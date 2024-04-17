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

#include "iostream"

#include "common/UnderlayConfigurator.h"
#include "common/GlobalStatistics.h"

#include "overlay/myoverlay/MyOverlay_m.h"

#include "overlay/myoverlay/MyOverlay.h"


// Important! This line must be present for each module you extend (see BaseApp)
Define_Module(MyOverlay);

// Called when the module is being initialized
void MyOverlay::initializeOverlay(int stage)
{
    // see BaseApp.cc
    if (stage != MIN_STAGE_OVERLAY) return;

    // init rpc timer
    rpcTimer = new cMessage("RPC timer");
    scheduleAt(simTime() + 5, rpcTimer);
}

// Called when the module is ready to join the overlay
void MyOverlay::joinOverlay()
{
    // nothing to do, tell the simulator that we're ready
    setOverlayReady(true);
}

void MyOverlay::handleTimerEvent(cMessage *msg)
{
    if (msg == rpcTimer) {
        // reschedule the timer
        scheduleAt(simTime() + 5, rpcTimer);

        // if the simulator is still busy creating the network, let's wait a bit longer
        if (underlayConfigurator->isInInitPhase()) return;

        // request a key from the central host
        TransportAddress *tad = new TransportAddress(IPv4Address("1.0.0.1"), 1024);
        getKey(*tad);
    }
}

// Called when the module is about to be destroyed
void MyOverlay::finishOverlay()
{
    // remove this node from the overlay
    setOverlayReady(false);

    // save the statistics (see BaseApp)
    // globalStatistics->addStdDev("MyOverlay: Dropped packets", numDropped);
}

// call to get key from central host
void MyOverlay::getKey(const TransportAddress &address)
{
    KeyCall *msg = new KeyCall();

    EV << thisNode << ": (RPC) Sending key request to "
       << address.getIp().str() << "!" << std::endl;

    sendRouteRpcCall(OVERLAY_COMP, address, msg);
}

// after receiving key, call to subscribe to messages from central host
void MyOverlay::subscribe(int key)
{
    KeySubscriptionMessage *msg;
    msg = new KeySubscriptionMessage();
    msg->setMessageType(SUBSCRIBE);
    msg->setSenderAddress(thisNode);
    msg->setKey(key);
    msg->setByteLength(128);

    EV << thisNode.getIp() << ": sending subscription packet..."
       << std::endl;

    TransportAddress *tad = new TransportAddress(IPv4Address("1.0.0.1"), 1024);
    EV << "BEFORE" << std::endl;
    BaseOverlayMessage *outgoing = check_and_cast<BaseOverlayMessage*>(msg);
    EV << "AFTER" << std::endl;
    sendMessageToUDP(*tad, outgoing);
    EV << "MOIST EAFTER" << std::endl;
}

// handles incoming udp messages
void MyOverlay::handleUDPMessage(BaseOverlayMessage* msg)
{
    // cast to our message type
    TheLatestMessage *mmsg = dynamic_cast<TheLatestMessage*>(msg);

    // check
    if (mmsg)
    {
        EV << thisNode.getIp() << ": received subscription message "
           << mmsg->getTheLatest()
           << std::endl;
    }

    delete msg;
}

// Called when an RPC we sent has timed out.
// Don't delete msg here!

void MyOverlay::handleRpcTimeout(BaseCallMessage* msg,
                         const TransportAddress& dest,
                         cObject* context, int rpcId,
                         const OverlayKey&)
{
    // Same macros as in handleRpc

    // start a switch
    RPC_SWITCH_START(msg);
    // shortened parameter etcet.c
    RPC_ON_CALL(Key) {
        KeyCall *mrpc = (KeyCall*)msg;
        callbackKeyTimeout();
    }
    // end the switch
    RPC_SWITCH_END();
}

// Called when we receive an RPC response from another node.
// Don't delete msg here!

void MyOverlay::handleRpcResponse(BaseResponseMessage* msg,
                                  cObject* context,
                                  int rpcId,
                                  simtime_t rtt)
{
    // The macros are here similar. Just use RPC_ON_RESPONSE instead of RPC_ON_CALL.

    // start a switch
    RPC_SWITCH_START(msg);
    // custom rpc response if key
    RPC_ON_RESPONSE(Key) {
        KeyResponse *mrpc = (KeyResponse*)msg;
        callbackKey(mrpc->getActivationKey());
    }
    // end the switch
    RPC_SWITCH_END();
}

void MyOverlay::callbackKey(int activationKey)
{
    EV << thisNode << ": (RPC) Got response of key "
       << activationKey << std::endl;

    subscribe(activationKey);
}

void MyOverlay::callbackKeyTimeout()
{
    EV << thisNode << ": (RPC) key request timed out..."
       << std::endl;
}
