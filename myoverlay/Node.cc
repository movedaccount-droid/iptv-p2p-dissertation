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

#include "iostream"

#include "common/UnderlayConfigurator.h"
#include "common/GlobalStatistics.h"

#include "Node.h"
#include "Coolstreaming_m.h"

Define_Module(Node);

// overlay routines
// called at overlay construction
void Node::initializeOverlay(int stage) {
    if (stage != MIN_STAGE_OVERLAY) return;
    partnership_manager.init(this, par("bm_exchange_interval"), par("M"));
    membership_manager.init(this,
            par("c"),
            par("scamp_resubscription_interval"),
            par("scamp_heartbeat_interval"),
            par("scamp_heartbeat_failure_interval"),
            par("M"));
    origin = par("origin");
    leaving = false;
}

// called at overlay join time. configures timers
void Node::joinOverlay() {
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
            membership_manager.receive_membership_message(membership);
        } else if (Heartbeat* heartbeat = dynamic_cast<Heartbeat*>(msg)) {
            membership_manager.receive_heartbeat_message(heartbeat);
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
    RPC_ON_CALL(Inview) {
        membership_manager.receive_inview_message_and_respond(_InviewCall);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_CALL(GetDeputy) {
        membership_manager.receive_get_deputy_message_and_respond(_GetDeputyCall);
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_CALL(GetCandidatePartners) {
        std::vector<TransportAddress> candidates = membership_manager.get_partner_candidates(_GetCandidatePartnersCall->getFrom());
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
    RPC_ON_RESPONSE(Inview) {
        membership_manager.receive_inview_ack();
        RPC_HANDLED = true;
        break;
    }
    RPC_ON_RESPONSE(GetDeputy) {
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
            membership_manager.send_get_deputy_message(TransportAddress(IPv4Address("1.0.0.1"), 1024));
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
