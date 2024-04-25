//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "../coolstreaming/Node.h"

#include "iostream"
#include <functional>
#include <iostream>
#include <random>
#include <set>
#include <utility>
#include <unordered_set>

#include "../coolstreaming/Coolstreaming_m.h"
#include "common/UnderlayConfigurator.h"
#include "common/GlobalStatistics.h"


Define_Module(Node);

// overlay routines
// called at overlay construction
void Node::initializeOverlay(int stage) {
    if (stage != MIN_STAGE_OVERLAY) return;

    origin = par("origin");
    bool is_first_origin = this->getThisNode().getIp().str() == par("first_origin_ip").stdstringValue();
    auto origin_tad_par = is_first_origin ? "second_origin_ip" : "first_origin_ip";
    origin_tad = TransportAddress(IPv4Address(par(origin_tad_par).stringValue()), 1024);
    heterogeneous_upload = par("heterogeneous_upload");
    arrow_type = par("arrow_type").stdstringValue();
    leaving = false;

    const int Mb_to_b = 1e+6;
    const int Kb_to_b = 1e+3;
    int block_size_bits = par("bitrate_kbps").intValue() * par("block_length_s").intValue() * Kb_to_b;

    if (heterogeneous_upload) {
        // set our bandwidth randomly between 100-900Kbps, biased towards the low end
        std::mt19937 rng(rand());
        std::fisher_f_distribution<double> distribution(15, 10);
        bandwidth = origin ? 15 * Mb_to_b : (distribution(rng) * 133.33 + 100) * Kb_to_b;
    } else {
        // we're probably just testing. set our bandwidth to 3 blocks a second
        bandwidth = block_size_bits * par("block_length_s").intValue() * 3;
    }

    membership_manager.init(this,
            origin_tad,
            bandwidth,
            par("c"),
            par("scamp_resubscription_interval"),
            par("scamp_heartbeat_interval"),
            par("scamp_heartbeat_failure_interval"),
            par("M"));
    stream_manager.init(this,
            par("substream_count"),
            par("exchange_interval_s"),
            par("buffer_size"),
            par("block_length_s"),
            block_size_bits,
            par("ts"),
            par("tp"),
            par("partner_percentage_threshold_to_start_playout"),
            par("display_string").stdstringValue() == std::string("STREAM"));
    init_partnerlink_manager();
}

// called at overlay join time. configures timers
void Node::joinOverlay() {
    if (heterogeneous_upload) {
        cChannel* channel = getParentModule()->getParentModule()->gate("pppg$o", 0)->getTransmissionChannel();
        dynamic_cast<cDatarateChannel*>(channel)->setDatarate(bandwidth);
    }
    membership_manager.join_overlay();
    setOverlayReady(true);
}

// called at overlay leave time
void Node::finishOverlay() {
    leaving = true;
    membership_manager.leave_overlay();
    partnerlink_manager.leave_overlay();
    stream_manager.leave_overlay();
    setOverlayReady(false);
}

void Node::init_partnerlink_manager() {
    partnerlink_manager = PartnerlinkManager();
    partnerlink_manager.init(this,
            par("M"),
            origin ? 0 : par("M"), // so that our origin starts assuming 0 partners as it should
            par("partnership_timeout_s"),
            par("panic_timeout_s"),
            par("panic_split_timeout_s"),
            par("switch_interval_s"),
            par("substream_count"),
            par("tp"),
            par("display_string").stdstringValue() == std::string("PARTNER"));
    if (origin) {
        // join our two origins, so that we have a starter link to split from
        partnerlink_manager.send_link_origin_nodes_message(origin_tad);
    }
    partnerlink_manager.update_display_string();
}

// rpc handling
void Node::handleUDPMessage(BaseOverlayMessage* msg) {
    // we have this at the top for optimization
    if (Block* block = dynamic_cast<Block*>(msg)) {
        stream_manager.receive_block_message(block);
    } else if (Heartbeat* heartbeat = dynamic_cast<Heartbeat*>(msg)) {
        membership_manager.receive_heartbeat_message(heartbeat);
    } else if (Unsubscription* unsubscription = dynamic_cast<Unsubscription*>(msg)) {
        membership_manager.receive_unsubscribe_message(unsubscription);
    } else if (PanicSplitFound* panic_split_found_msg = dynamic_cast<PanicSplitFound*>(msg)) {
        // this seems a bad idea to allow while leaving but there is logic:
        // if we ignore this message the incoming node loses two links and our partner loses one.
        // if we return it as normal, the incoming node loses the one link that will time out as we leave.
        // ideally we would define have another return type that handles this case, instructing only
        // to connect to the first node - but we have a deadline!
        partnerlink_manager.receive_panic_split_found_message(panic_split_found_msg);
    } else if (PanicMsg* panic_msg = dynamic_cast<PanicMsg*>(msg)) {
        // this and panic_split have contained cases for leaving nodes
        partnerlink_manager.receive_panic_message(panic_msg);
    } else if (PanicSplitMsg* panic_split_msg = dynamic_cast<PanicSplitMsg*>(msg)) {
        partnerlink_manager.receive_panic_split_message(panic_split_msg);
    } else if (!leaving) {
        if (Membership* membership = dynamic_cast<Membership*>(msg)) {
            membership_manager.receive_membership_message(membership);
        } else if (LinkOriginNodes* link_origin_nodes = dynamic_cast<LinkOriginNodes*>(msg)) {
            partnerlink_manager.receive_link_origin_nodes_message(link_origin_nodes);
        } else if (BufferMapMsg* buffer_map = dynamic_cast<BufferMapMsg*>(msg)) {
            partnerlink_manager.receive_buffer_map_message(buffer_map);
            stream_manager.receive_buffer_map_message(buffer_map);
            if (!stream_manager.playing) {
                double partner_percent = partnerlink_manager.get_partner_percent_out_of_m();
                int starting_index = partnerlink_manager.get_starting_index();
                if (stream_manager.should_start(partner_percent) && starting_index >= 0) {
                    stream_manager.start(starting_index);
                }
            }
        } else if (Recover* recover = dynamic_cast<Recover*>(msg)) {
            partnerlink_manager.receive_recover_message(recover);
        }
    }

    delete msg;
}

bool Node::handleRpcCall(BaseCallMessage* msg) {
    RPC_SWITCH_START(msg);
    RPC_ON_CALL(Split) {
        partnerlink_manager.receive_split_message_and_try_split_with_partner(_SplitCall);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_CALL(TrySplit) {
        partnerlink_manager.receive_try_split_message_and_try_split(_TrySplitCall);
        RPC_HANDLED = true;
        break;
    }
    if (leaving) return true;
    RPC_ON_CALL(Inview) {
        membership_manager.receive_inview_message_and_respond(_InviewCall);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_CALL(GetDeputy) {
        membership_manager.receive_get_deputy_message_and_respond(_GetDeputyCall, stream_manager.get_playout_index());
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_CALL(GetCandidatePartners) {
        membership_manager.receive_get_candidate_partners_message_and_respond(_GetCandidatePartnersCall);
        RPC_HANDLED = true;
        break;
    }
    RPC_SWITCH_END();
    return RPC_HANDLED;
}

void Node::handleRpcResponse(BaseResponseMessage* msg,
                          cObject* context,
                          int rpcId,
                          simtime_t rtt) {
    RPC_SWITCH_START(msg);
    RPC_ON_RESPONSE(Split) {
        partnerlink_manager.receive_split_response(_SplitResponse);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_RESPONSE(TrySplit) {
        partnerlink_manager.receive_try_split_response(_TrySplitResponse);
        RPC_HANDLED = true;
        break;
    }
    if (leaving) return;
    RPC_ON_RESPONSE(Inview) {
        membership_manager.receive_inview_ack();
        RPC_HANDLED = true;
        break;
    }
    // TODO: remove starting block from deputy call
    RPC_ON_RESPONSE(GetDeputy) {
        if (partnerlink_manager.needs_deputy) {
            partnerlink_manager.send_get_candidate_partners_message(_GetDeputyResponse->getDeputy());
        }
        if (membership_manager.needs_deputy) {
            membership_manager.receive_get_deputy_response(_GetDeputyResponse);
        }
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_RESPONSE(GetCandidatePartners) {
        partnerlink_manager.receive_get_candidate_partners_response(_GetCandidatePartnersResponse);
        RPC_HANDLED = true;
        break;
    }
    RPC_SWITCH_END();
}

void Node::handleRpcTimeout(BaseCallMessage* msg,
                         const TransportAddress& dest,
                         cObject* context, int rpcId,
                         const OverlayKey&) {
    RPC_SWITCH_START(msg);
    RPC_ON_CALL(TrySplit) {
        partnerlink_manager.timeout_try_split_response(_TrySplitCall);
        RPC_HANDLED = true;
        break;
    }
    if (leaving) return;
    RPC_ON_CALL(Inview) {
        membership_manager.timeout_inview_ack(_InviewCall);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_CALL(GetDeputy) {
        membership_manager.timeout_get_deputy_response(_GetDeputyCall);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_CALL(GetCandidatePartners) {
        if (!origin) {
            membership_manager.send_get_deputy_message(origin_tad);
        }
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_CALL(Split) {
        partnerlink_manager.timeout_split_response(_SplitCall);
        RPC_HANDLED = true;
        break;
    }
    RPC_SWITCH_END();
}

void Node::handleTimerEvent(cMessage *msg) {
    if (leaving) return;
    if (msg == membership_manager.resubscription_timer) {
        membership_manager.resubscribe();
    } else if (msg == membership_manager.send_heartbeat_timer) {
        membership_manager.send_heartbeats();
    } else if (msg == membership_manager.no_heartbeat_timer) {
        membership_manager.no_heartbeat();
    } else if (msg == partnerlink_manager.switch_timer) {
        try {
            auto to = membership_manager.random_mcache_entry(partnerlink_manager.get_partner_tads()).first;
            partnerlink_manager.start_switch_from_mcache(to);
        } catch (const char* c) {
            partnerlink_manager.reset_switch_timer();
        }
    } else if (msg == stream_manager.playout_timer) {
        stream_manager.playout();
    } else if (msg == stream_manager.exchange_timer) {
        std::map<TransportAddress, std::vector<int>> latest_blocks = partnerlink_manager.get_partner_latest_blocks();
        std::map<TransportAddress, TransportAddress> associations = partnerlink_manager.get_associations();
        bool panicking = partnerlink_manager.get_panic_status() != Nominal;
        // TODO: possibly include k-order balancing for origin node
        // TODO: acutally handle origin node having all blocks all the time
        stream_manager.reselect_parents_and_exchange_partners(latest_blocks, associations, panicking);
    } else if (msg == stream_manager.catchup_timer) {
        stream_manager.catchup_children();
    } else if (msg == partnerlink_manager.panic_timeout_timer) {
        partnerlink_manager.timeout_panic();
    } else if (msg == partnerlink_manager.panic_split_timeout_timer) {
        partnerlink_manager.timeout_panic_split();
    } else if (Failure* failure = dynamic_cast<Failure*>(msg)) {
        partnerlink_manager.read_failure_timer_and_fail_connection(failure);
    } else if (TotalPartnerFailure* total_partner_failure = dynamic_cast<TotalPartnerFailure*>(msg)) {
        init_partnerlink_manager();
        membership_manager.send_get_deputy_message(origin_tad);
    }
}

// arrow drawing/handling
void Node::set_arrow(TransportAddress tad, std::string requested_type, bool enable) {
    if (requested_type != arrow_type) return;
    deleteOverlayNeighborArrow(tad);
    if (!enable) return;
    if (arrow_type == std::string("MCACHE") && requested_type == std::string("MCACHE")) {
        showOverlayNeighborArrow(tad, false, "ls=#B99DE8,2,s");
    } else if (arrow_type == std::string("PARTNER") && requested_type == std::string("PARTNER")) {
        showOverlayNeighborArrow(tad, false, "ls=#334455,3,s");
    } else if (arrow_type == std::string("STREAM") && requested_type == std::string("STREAM")) {
        showOverlayNeighborArrow(tad, false, "ls=#774433,3,s");
    }
}

void Node::add_std_dev(const std::string& name, double value) {
    globalStatistics->addStdDev(name, value);
}

// sending messages. our object structure is Bad
void Node::send_rpc(TransportAddress tad, BaseCallMessage* msg) {
    sendRouteRpcCall(OVERLAY_COMP, tad, msg);
}

void Node::send_rpc_response(BaseCallMessage* call, BaseResponseMessage* response) {
    sendRpcResponse(call, response);
}

// boilerplate
int Node::getMaxNumRedundantNodes()
{
    return 0;
}

NodeVector* Node::findNode(const OverlayKey &key, int numRedundantNodes, int numSiblings, BaseOverlayMessage *msg)
{
    NodeVector* nv = new NodeVector();
    return nv;
}



Node::~Node() {}
