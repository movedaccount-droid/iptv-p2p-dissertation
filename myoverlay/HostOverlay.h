//
// Copyright (C) 2009 Institut fuer Telematik, Universitaet Karlsruhe (TH)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

/**
 * @author Antonio Zea
 */

#ifndef _MYOVERLAY_
#define _MYOVERLAY_

#include "common/BaseOverlay.h"
#include "common/TransportAddress.h"

class HostOverlay : public BaseOverlay
{
private:
    // RPC timer
    cMessage *rpcTimer;

    // rpc state
    std::set<TransportAddress> subscribers;
    int latestIndex;

    // routine for RPC timer
    void handleTimerEvent(cMessage *msg);

    // overlay routines
    void initializeOverlay(int stage);                      // called when the overlay is being initialized
    void joinOverlay();                                     // called when the node is ready to join the overlay
    void finishOverlay();                                   // called when the module is about to be destroyed

    // called when receiving any udp message from overlay
    void handleUDPMessage(BaseOverlayMessage* msg);
    void sendSubscription(const TransportAddress& ip);

    // internal handling of RPCs
    bool handleRpcCall(BaseCallMessage *msg);                    // called when we receive an RPC from another node

public:
    HostOverlay() { rpcTimer = NULL; };
    ~HostOverlay() { cancelAndDelete(rpcTimer); };
};

#endif
