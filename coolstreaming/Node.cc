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

// arrow drawing/handling
void Node::set_arrow(TransportAddress tad, std::string requested_type, bool enable) {
    if (requested_type != arrow_type) return;
    deleteOverlayNeighborArrow(tad);
    if (!enable) return;
    if (arrow_type == std::string("MCACHE") && requested_type == std::string("MCACHE")) {
        showOverlayNeighborArrow(tad, false, "ls=#B99DE8,2,s");
    } else if (arrow_type == std::string("PARTNER") && requested_type == std::string("PARTNER")) {
        showOverlayNeighborArrow(tad, false, "ls=#334455,3,s");
    }
}

// overlay routines
// called at overlay construction
void Node::initializeOverlay(int stage) {
    if (stage != MIN_STAGE_OVERLAY) return;

    origin = par("origin");
    origin_tad = TransportAddress(IPv4Address(par("origin_ip").stringValue()), 1024);
    heterogeneous_upload = par("heterogeneous_upload");
    arrow_type = par("arrow_type").stdstringValue();
    leaving = false;

    const int Kb_to_b = 1e+3;
    int block_size_bits = par("bitrate_kbps").intValue() * par("buffer_size").intValue() * Kb_to_b;

    partnership_manager.init(this, par("switch_interval"), par("M"));
    membership_manager.init(this,
            origin_tad,
            par("c"),
            par("scamp_resubscription_interval"),
            par("scamp_heartbeat_interval"),
            par("scamp_heartbeat_failure_interval"),
            par("M"));
    buffer.init(this,
            par("playout_interval"),
            par("buffer_size"),
            par("start_threshold"),
            block_size_bits);
    scheduler.init(this,
            block_size_bits,
            par("bm_exchange_interval"),
            par("block_length_s"),
            par("buffer_size"));
}

// called at overlay join time. configures timers
void Node::joinOverlay() {
    if (heterogeneous_upload) {
        // set our upload speed randomly between 100-900Kbps
        const int Mb_to_b = 1e+6;
        const int Kb_to_b = 1e+3;

        std::mt19937 rng(rand());
        std::fisher_f_distribution<double> distribution(15, 10);
        double datarate = origin ? 15 * Mb_to_b : (distribution(rng) * 133.33 + 100) * Kb_to_b;
        cChannel* channel = getParentModule()->getParentModule()->gate("pppg$o", 0)->getTransmissionChannel();
        dynamic_cast<cDatarateChannel*>(channel)->setDatarate(datarate);
    }

    membership_manager.join_overlay();
    setOverlayReady(true);
}

// called at overlay leave time
void Node::finishOverlay() {
    leaving = true;
    membership_manager.leave_overlay();
    setOverlayReady(false);
}

// rpc handling
void Node::handleUDPMessage(BaseOverlayMessage* msg) {
    if (!leaving) {
        if (Membership* membership = dynamic_cast<Membership*>(msg)) {
            bool accepted = membership_manager.receive_membership_message(membership);
            if (accepted) partnership_manager.insert_new_partner_if_needed(membership->getTad());
        } else if (Heartbeat* heartbeat = dynamic_cast<Heartbeat*>(msg)) {
            membership_manager.receive_heartbeat_message(heartbeat);
        } else if (Partnership* partnership = dynamic_cast<Partnership*>(msg)) {
            partnership_manager.receive_partnership_message(partnership);
        } else if (PartnershipEnd* partnership_end = dynamic_cast<PartnershipEnd*>(msg)) {
            try {
                TransportAddress replacement = membership_manager.random_mcache_entry(partnership_manager.get_partner_tads()).first;
                partnership_manager.receive_partnership_end_message(partnership_end, replacement);
            } catch (const char* c) {
                partnership_manager.erase_partner(partnership_end->getFrom());
            }
        } else if (BufferMap* buffer_map = dynamic_cast<BufferMap*>(msg)) {
            partnership_manager.receive_buffer_map_message(buffer_map);
            // TODO: trying here for now. but this might be too spammy
            auto partners = partnership_manager.get_partners();
            auto expected_set = buffer.get_expected_set();
            auto playout_index = buffer.get_playout_index();
            scheduler.request_buffer_map_blocks(expected_set, partners, playout_index);
        }
    }
    if (Unsubscription* unsubscription = dynamic_cast<Unsubscription*>(msg)) {
        membership_manager.receive_unsubscribe_message(unsubscription);
    } else if (GossipedUnsubscription* gossiped_unsubscription = dynamic_cast<GossipedUnsubscription*>(msg)) {
        membership_manager.receive_gossiped_unsubscribe_message(gossiped_unsubscription);
    }
    delete msg;
}

bool Node::handleRpcCall(BaseCallMessage* msg) {
    if (leaving) return true;
    RPC_SWITCH_START(msg);
    RPC_ON_CALL(Block) {
        buffer.receive_block_message_and_respond(_BlockCall);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_CALL(Inview) {
        membership_manager.receive_inview_message_and_respond(_InviewCall);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_CALL(GetDeputy) {
        membership_manager.receive_get_deputy_message_and_respond(_GetDeputyCall, buffer.playout_index);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_CALL(GetCandidatePartners) {
        std::set<TransportAddress> candidates = membership_manager.get_partner_candidates(_GetCandidatePartnersCall->getFrom(), partnership_manager.partners.size());
        partnership_manager.receive_get_candidate_partners_message_and_respond(_GetCandidatePartnersCall, candidates);
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
    if (leaving) return;
    RPC_SWITCH_START(msg);
    RPC_ON_RESPONSE(Block) {
        buffer.receive_block_response(_BlockResponse);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_RESPONSE(Inview) {
        membership_manager.receive_inview_ack();
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_RESPONSE(GetDeputy) {
        buffer.set_playout_index(_GetDeputyResponse->getBlock_index());
        partnership_manager.get_candidate_partners_from_deputy(_GetDeputyResponse->getDeputy());
        membership_manager.receive_get_deputy_response(_GetDeputyResponse);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_RESPONSE(GetCandidatePartners) {
        partnership_manager.receive_get_candidate_partners_response(_GetCandidatePartnersResponse);
        RPC_HANDLED = true;
        break;
    }
    RPC_SWITCH_END();
}

void Node::handleRpcTimeout(BaseCallMessage* msg,
                         const TransportAddress& dest,
                         cObject* context, int rpcId,
                         const OverlayKey&) {
    if (leaving) return;
    RPC_SWITCH_START(msg);
    RPC_ON_CALL(Block) {
        scheduler.timeout_block_response(_BlockCall);
        RPC_HANDLED = true;
        break;
    }
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
    } else if (msg == partnership_manager.switch_timer) {
        try {
            TransportAddress to = membership_manager.random_mcache_entry(partnership_manager.get_partner_tads()).first;
            partnership_manager.score_and_switch(to);
        } catch (const char* c) {
            partnership_manager.reset_switch_timer();
        }
    } else if (msg == buffer.playout_timer) {
        buffer.playout();
    } else if (msg == scheduler.exchange_timer) {
        std::set<TransportAddress> partners = partnership_manager.get_partner_tads();
        std::unordered_set<int> buffer_map = buffer.get_buffer_map();
        scheduler.exchange(partners, buffer_map);
    }
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
