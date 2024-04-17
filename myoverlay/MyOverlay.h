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

#ifndef _HOSTOVERLAY_
#define _HOSTOVERLAY_

#include "common/BaseOverlay.h"

class MyOverlay : public BaseOverlay
{
private:
    // RPC timer
    cMessage *rpcTimer;

    // routine for RPC timer
    void handleTimerEvent(cMessage *msg);

    // overlay routines
    void initializeOverlay(int stage);                      // called when the overlay is being initialized
    void joinOverlay();                                     // called when the node is ready to join the overlay
    void finishOverlay();                                   // called when the module is about to be destroyed

    // call to request custom key rpc from central host
    void getKey(const TransportAddress &address);
    // called if custom key rpc times out
    virtual void callbackKeyTimeout();
    // called on custom key rpc response
    virtual void callbackKey(int activationKey);

    // call to send subscription request with key
    void subscribe(int key);
    // called when receiving subscription events
    void handleUDPMessage(BaseOverlayMessage* msg);

    // internal handling of RPCs
    void handleRpcResponse(BaseResponseMessage* msg,         // called when we receive an RPC response from another node
                              cObject* context,
                              int rpcId,
                              simtime_t rtt);
    void handleRpcTimeout(BaseCallMessage* msg,                 // called when an RPC times out
                             const TransportAddress& dest,
                             cObject* context, int rpcId,
                             const OverlayKey&);

public:
    MyOverlay() { rpcTimer = NULL; };
    ~MyOverlay() { cancelAndDelete(rpcTimer); };
};

#endif
