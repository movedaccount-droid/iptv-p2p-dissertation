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

#ifndef OVERLAY_COOLSTREAMING_NODE_H_
#define OVERLAY_COOLSTREAMING_NODE_H_

#include <unordered_set>

#include "../coolstreaming/Buffer.h"
#include "../coolstreaming/MembershipManager.h"
#include "../coolstreaming/PartnershipManager.h"
#include "../coolstreaming/Scheduler.h"
#include "common/BaseOverlay.h"

class Node : public BaseOverlay {

    // node components - see paper fig. 1
    PartnershipManager partnership_manager;
    MembershipManager membership_manager;
    Buffer buffer;
//    Scheduler scheduler;

    TransportAddress temp_gettad();

    // overlay routines
    void initializeOverlay(int stage); // called at overlay construction
    void joinOverlay(); // called at overlay join time. configures timers
    void finishOverlay(); // called at overlay leave time

    // rpc handling
    void handleUDPMessage(BaseOverlayMessage* msg);
    bool handleRpcCall(BaseCallMessage* msg);
    void handleRpcResponse(BaseResponseMessage* msg,
                              cObject* context,
                              int rpcId,
                              simtime_t rtt);
    void handleRpcTimeout(BaseCallMessage* msg,
                             const TransportAddress& dest,
                             cObject* context, int rpcId,
                             const OverlayKey&);


    // timer handling
    void handleTimerEvent(cMessage *msg);

    // boilerplate
    int getMaxNumRedundantNodes();
    NodeVector* findNode(const OverlayKey &key, int numRedundantNodes, int numSiblings, BaseOverlayMessage *msg);

public:
    bool origin; // if we are the origin node
    std::string arrow_type; // type of arrow to draw
    bool leaving; // if we are leaving the network

    // arrow drawing/handling
    void set_arrow(TransportAddress tad, std::string requested_type, bool enable);

    // message sending. our object structure is bad
    void send_rpc(TransportAddress tad, BaseCallMessage* msg);
    void send_rpc_response(BaseCallMessage* call, BaseResponseMessage* response);

    Node(): membership_manager(), partnership_manager(), buffer() {};
    virtual ~Node();
};

#endif /* OVERLAY_COOLSTREAMING_NODE_H_ */