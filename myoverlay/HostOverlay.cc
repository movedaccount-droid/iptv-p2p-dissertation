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
#include <unordered_set>

#include "common/UnderlayConfigurator.h"
#include "common/GlobalStatistics.h"

#include "overlay/myoverlay/MyOverlay_m.h"

#include "overlay/myoverlay/HostOverlay.h"


// Important! This line must be present for each module you extend (see BaseApp)
Define_Module(HostOverlay);

// Called when the module is being initialized
void HostOverlay::initializeOverlay(int stage)
{
    // skip second call of initialize, after all modules have been loaded
    if (stage != MIN_STAGE_OVERLAY) return;

    // setup rpc timer
    rpcTimer = new cMessage("RPC timer");
    scheduleAt(simTime() + 5, rpcTimer);

    // setup variables
    latestIndex = 0;
}


// Called when the module is ready to join the overlay
void HostOverlay::joinOverlay()
{
    // we have no overlay-specific information,
    // so we just tell the simulator that we're ready
    setOverlayReady(true);
}

// called whenever self-set timer event expires
void HostOverlay::handleTimerEvent(cMessage *msg)
{

    // check type of message as always
    if (msg == rpcTimer) {
        // reschedule the timer
        scheduleAt(simTime() + 5, rpcTimer);

        // if the simulator is still busy creating the network, let's wait a bit longer
        if (underlayConfigurator->isInInitPhase()) return;

        // flood subscribers with the latest
        EV << "ITERATING\n\n\n" << std::endl;
        for(auto &ip : subscribers) {
            EV << "FOUND " << ip.getIp().str()
               << std::endl;
            sendSubscription(ip);
        }
    }
}

// Called when the module is about to be destroyed
void HostOverlay::finishOverlay()
{
    // remove this node from the overlay
    setOverlayReady(false);

    // save the statistics (see BaseApp)
    // globalStatistics->addStdDev("MyOverlay: Dropped packets", numDropped);
}

// Handle an incoming Call message
// Only delete msg if the RPC is handled here, and you won't respond using sendRpcResponse!
bool HostOverlay::handleRpcCall(BaseCallMessage *msg)
{
    // There are many macros to simplify the handling of RPCs. The full list is in <OverSim>/src/common/RpcMacros.h.

    // start a switch
    RPC_SWITCH_START(msg);
    // shortened parameter!!
    RPC_ON_CALL(Key) {
        // respond to keyrequests with constant key
        KeyCall *mrpc = (KeyCall*)msg;

        KeyResponse *rrpc = new KeyResponse();
        rrpc->setActivationKey(29);

        sendRpcResponse(mrpc, rrpc);

        // set rpc to handled and break to avoid segfault
        RPC_HANDLED = true;
        break;
    }
    // end the switch
    RPC_SWITCH_END();

    // return whether we handled the message or not.
    // don't delete unhandled messages!
    return RPC_HANDLED;
}

// called when receiving any udp message
void HostOverlay::handleUDPMessage(BaseOverlayMessage* msg)
{
    // cast to our message type
    KeySubscriptionMessage *mmsg = dynamic_cast<KeySubscriptionMessage*>(msg);

    // check if it was valid. we can repeat this to "switch"
    // on the underlying message class
    if (mmsg && mmsg->getMessageType() == SUBSCRIBE)
    {
        EV << thisNode.getIp() << ": received udp packet from "
           << mmsg->getSenderAddress() << " with number "
           << mmsg->getKey() << ", saving..."
           << std::endl;
        if (mmsg->getKey() == 29)
        {
            subscribers.insert(mmsg->getSenderAddress());
        }
    }

    delete msg;
}

// send a subscriber the latest by udp
void HostOverlay::sendSubscription(const TransportAddress& ip)
{
    TheLatestMessage *msg;
    msg = new TheLatestMessage();
    msg->setLatestIndex(latestIndex++);
    msg->setTheLatest("The Latest News: this");
    sendMessageToUDP(ip, msg);
}
