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

#include <cstdlib>
#include "MembershipManager.h"
#include "mCacheEntry.h"
#include "Node.h"
#include "Coolstreaming_m.h"

// utility functions
#define setOrReplace(timer, name, offset) if (timer != NULL && timer->isScheduled()) { \
    parent->cancelEvent(timer); \
} else if (!timer) { \
    timer = new cMessage(name); \
} \
parent->scheduleAt(simTime() + offset, timer)

mCacheEntry MembershipManager::random_mcache_entry(TransportAddress exclude) {
    // this is hacky and very dumb
    int exclusions;
    if (!exclude.isUnspecified() && mcache_contains_tad(exclude)) {
        exclusions = 1;
    } else {
        exclusions = 0;
    }
    if (mCache.size() - exclusions == 0) {
        throw "no entries in cache";
    }

    int random = rand() % mCache.size();
    mCacheEntry ran = mCache[random];

    if (!exclude.isUnspecified() && ran.tad == exclude) {
        return random_mcache_entry(exclude);
    } else if (ran.expired()) {
        remove_mcache_entry(ran.tad);
        parent->getParentModule()->getParentModule()->bubble(std::string("expired random ip ").append(ran.tad.getIp().str()).append("...").c_str());
        return random_mcache_entry(exclude);
    } else {
        return ran;
    }
}

bool MembershipManager::mcache_contains_tad(TransportAddress tad) {
    for (mCacheEntry node : mCache) {
        if (node.tad == tad) return true;
    }
    return false;
}

void MembershipManager::insert_mcache_entry(int seq_num, TransportAddress tad, int num_partner, simtime_t ttl) {
    remove_mcache_entry(tad);
    for (mCacheEntry node : mCache) {
        parent->deleteOverlayNeighborArrow(node.tad);
        parent->showOverlayNeighborArrow(node.tad, false, "ls=red,1");
    }
    parent->showOverlayNeighborArrow(tad, false, "ls=red,1");
    mCacheEntry insert(seq_num, tad, num_partner, ttl);
    // TODO: we need to run a similar check for partner candidates,
    // TODO: we beed to u a similar check for when creating partnerships
    if (insert.expired()) return;
    mCache.push_back(insert);
}

void MembershipManager::remove_mcache_entry(TransportAddress tad) {
    parent->deleteOverlayNeighborArrow(tad);
    for (auto i = mCache.begin(); i != mCache.end(); i++) {
        if (i->tad == tad) {
            mCache.erase(i);
            return;
        }
    }
}

void MembershipManager::remove_inview_entry(TransportAddress tad) {
    for (auto i = inview.begin(); i != inview.end(); i++) {
        if (*i == tad) {
            inview.erase(i);
            return;
        }
    }
}

// init
void MembershipManager::init(Node* p, int cin, int scr, int sch, int schf) {
    parent = p;
    c = cin;
    scamp_resubscription_interval = scr;
    scamp_heartbeat_interval = sch;
    scamp_heartbeat_failure_interval = schf;
}

void MembershipManager::join_overlay() {
    setOrReplace(resubscription_timer, "resubscription_timer", scamp_resubscription_interval);
    setOrReplace(unsubscription_timer, "unsubscription_timer", 300);
    setOrReplace(send_heartbeat_timer, "send_heartbeat_timer", scamp_heartbeat_interval);
    setOrReplace(no_heartbeat_timer, "no_heartbeat_timer", scamp_heartbeat_failure_interval);
    if (!parent->origin) {
        send_entry_membership_message(TransportAddress(IPv4Address("1.0.0.1"), 1024));
    }
    parent->getParentModule()->getParentModule()->bubble("joining...");
}

void MembershipManager::resubscribe() {
    inview = std::vector<TransportAddress>();
    setOrReplace(resubscription_timer, "resubscription_timer", scamp_resubscription_interval);
    try {
        send_membership_message(random_mcache_entry().tad);
        parent->getParentModule()->getParentModule()->bubble("resubscribing...");
    } catch (const char* c) {
        send_entry_membership_message(TransportAddress(IPv4Address("1.0.0.1"), 1024));
        EV << "[MembershipManager::resubscribe() @ " << parent->getThisNode().getIp() << "]\n"
           << "    attempted to resubscribe but had empty partial view, reentering at origin..."
           << endl;
        parent->getParentModule()->getParentModule()->bubble("reentering at origin...");
    }
}

void MembershipManager::unsubscribe() {
    parent->cancelAndDelete(unsubscription_timer);
    auto ic = mCache.begin();
    auto ii = inview.begin();
    if (ic != mCache.end()) {
        for (int i = 1; i <= static_cast<int>(inview.size()) - c - 1; ++i) {
            send_unsubscribe_message(*ii, false, ic->tad);
            send_unsubscribe_message(ic->tad, true, *ii);
            ++ii; ++ic;
            if (ic == mCache.end()) ic = mCache.begin();
        }
    }
    while (ii != inview.end()) {
        send_unsubscribe_message(*ii, false);
        ++ii;
    }
}

void MembershipManager::send_heartbeats() {
    for (mCacheEntry node : mCache) {
        send_heartbeat_message(node.tad);
    }
    // TODO: this needs to be replaced by a calculation based on block length
    setOrReplace(send_heartbeat_timer, "send_heartbeat_timer", scamp_heartbeat_interval);
}

void MembershipManager::no_heartbeat() {
    EV << "[MembershipManager::no_heartbeat() @ " << parent->getThisNode().getIp() << "]\n"
       << "    got not heartbeat and resubscribed..."
       << endl;
    parent->getParentModule()->getParentModule()->bubble("failed heartbeat, resubscribing...");
    resubscribe();
    setOrReplace(no_heartbeat_timer, "no_heartbeat_timer", scamp_heartbeat_failure_interval);
}

void MembershipManager::leave_overlay() {
    for (mCacheEntry node : mCache) {
        parent->deleteOverlayNeighborArrow(node.tad);
    }
    parent->cancelAndDelete(resubscription_timer);
    parent->cancelAndDelete(unsubscription_timer);
    parent->cancelAndDelete(send_heartbeat_timer);
    parent->cancelAndDelete(no_heartbeat_timer);
    parent = NULL;
}

// MEMBERSHIP MESSAGES // UDP
// advertises existence of node to recipients
// recipients may acknowledge and absorb message or pass it on
void MembershipManager::generate_membership_message(TransportAddress dest,
        int seq_num, TransportAddress tad, int num_partner,
        SimTime ttl, bool forwarded, bool entry, int uuid) {
    Membership* membership = new Membership();
    membership->setUuid(uuid);
    membership->setSeq_num(seq_num);
    membership->setTad(tad);
    membership->setNum_partner(num_partner);
    membership->setTtl(ttl);
    membership->setForwarded(forwarded);
    membership->setEntry(entry);
    parent->sendMessageToUDP(dest, membership);
}

void MembershipManager::send_entry_membership_message(TransportAddress tad) {
    generate_membership_message(
            tad,
            seq_num++,
            parent->getThisNode(),
            // TODO: get thi svalue from PartnerManager
            1,
            SimTime(scamp_resubscription_interval, SIMTIME_S),
            false,
            true
    );
}

void MembershipManager::send_membership_message(TransportAddress tad) {
    generate_membership_message(
            tad,
            seq_num++,
            parent->getThisNode(),
            // TODO: get thi svalue from PartnerManager
            1,
            SimTime(scamp_resubscription_interval, SIMTIME_S),
            false
    );
}

void MembershipManager::send_forced_membership_message(TransportAddress tad) {
    generate_membership_message(
            tad,
            seq_num++,
            parent->getThisNode(),
            // TODO: get thi svalue from PartnerManager
            1,
            SimTime(scamp_resubscription_interval, SIMTIME_S),
            true
    );
}

void MembershipManager::forward_membership_message(Membership* membership, TransportAddress tad) {
    generate_membership_message(
            tad,
            membership->getSeq_num(),
            membership->getTad(),
            membership->getNum_partner(),
            membership->getTtl(),
            true,
            membership->getEntry(),
            membership->getUuid()
    );
}

void MembershipManager::absorb_membership_message(Membership* membership) {
    insert_mcache_entry(membership->getSeq_num(),
            membership->getTad(),
            membership->getNum_partner(),
            membership->getTtl());
    generate_inview_message(membership->getTad());
}

void MembershipManager::receive_membership_message(Membership* membership) {
    if (!membership->getForwarded()) {
        if (mCache.size() == 0 && parent->origin) {
            // special case if we are the origin
            // so that we are always outputting video Somewhere
            parent->getParentModule()->getParentModule()->bubble("origin had no mcache, forced bar with node...");
            absorb_membership_message(membership);
            send_forced_membership_message(membership->getTad());
            return;
        }
        // algorithm 1: forward to all nodes of view
        int c = 0;
        for (mCacheEntry node : mCache) {
            if (node.expired()) {
                parent->getParentModule()->getParentModule()->bubble(std::string("expired forwarding ip ").append(node.tad.getIp().str()).append("...").c_str());
                remove_mcache_entry(node.tad);
                continue;
            }
            if (node.tad == membership->getTad()) continue;
            forward_membership_message(membership, node.tad);
            c++;
        };
        parent->getParentModule()->getParentModule()->bubble(std::string("FF'd to ").append(std::to_string(c)).append(" base nodes...").c_str());
        for (int j = 0; j < c; ++j) {
            try {
                forward_membership_message(membership, random_mcache_entry().tad);
            } catch (const char* c) {
                parent->getParentModule()->getParentModule()->bubble(std::string("dropped FF message for ").append(membership->getTad().getIp().str()).append("!!!").c_str());
                EV << "[MembershipManager::receive_membership_message() @ " << parent->getThisNode().getIp() << "]\n"
                   << "    attempted to first-forward membership message but had nobody to forward to, dropping...\n"
                   << "    the node is probably now dead !!!"
                   << endl;
                break;
            }
        }
        if (membership->getEntry()) {
            send_forced_membership_message(membership->getTad());
        }
    } else {
        // drop if seen too many times
        auto seenCount = uuidCounts.find(membership->getUuid());
        if (seenCount != uuidCounts.end()) {
            if (seenCount->second > 10) {
                parent->getParentModule()->getParentModule()->bubble("dropped message...");
                return;
            }
            uuidCounts[membership->getUuid()] = seenCount->second + 1;
        } else {
            uuidCounts.insert(std::make_pair(membership->getUuid(), 1));
        }
        // algorithm 2: add to cache or further forward
        double p = 1/(1 + mCache.size());
        bool success = rand() / RAND_MAX <= p;
        if (success && !mcache_contains_tad(membership->getTad())) {
            absorb_membership_message(membership);
            parent->getParentModule()->getParentModule()->bubble("absorbed message...");
        } else {
            try {
                forward_membership_message(membership, random_mcache_entry(membership->getTad()).tad);
                parent->getParentModule()->getParentModule()->bubble("forwarded message...");
            } catch (const char* c) {
                EV << "[MembershipManager::receive_membership_message() @ " << parent->getThisNode().getIp() << "]\n"
                   << "    attempted to forward membership message but had nobody to forward to, dropping..."
                   << endl;
            }
        }
    }
}

// INVIEW MESSAGES // TCP
// informs node of membership acceptance and requests initiation to
// inview list. if not received, the accepting node silently drops the acceptance
void MembershipManager::generate_inview_message(TransportAddress tad) {
    InviewCall* inview = new InviewCall();
    inview->setDestination(tad);
    inview->setAccepting_node(parent->getThisNode());
    parent->send_rpc(tad, inview);
}

void MembershipManager::receive_inview_message_and_respond(InviewCall* inview_call) {
    bool already_known = false;
    for (TransportAddress tad : inview) {
        if (tad == inview_call->getAccepting_node()) already_known = true;
    }
    if (!already_known) inview.push_back(inview_call->getAccepting_node());
    InviewResponse* inview_ack = new InviewResponse();
    parent->send_rpc_response(inview_call, inview_ack);
}

void MembershipManager::timeout_inview_ack(InviewCall* inview_call) {
    for (auto node = inview.begin(); node != inview.end(); ++node) {
        if (*node == inview_call->getDestination()) {
            inview.erase(node);
        }
    }
}

// simply receiving the message already cancelled the timeout, so we do nothing
void MembershipManager::receive_inview_ack() {}

// UNSUBSCRIBE MESSAGES // UDP
// informs nodes that they should swap their views. the paper is not
// 100% clear on implementation [do we also update inviews?] but we
// make a best effort
void MembershipManager::send_unsubscribe_message(TransportAddress tad, bool inview, TransportAddress replacement) {
    Unsubscription* unsubscription = new Unsubscription();
    unsubscription->setLeaving(parent->getThisNode());
    unsubscription->setReplacement(replacement);
    unsubscription->setInview(inview);
    parent->sendMessageToUDP(tad, unsubscription);
}

void MembershipManager::receive_unsubscribe_message(Unsubscription* unsubscription) {
    if (unsubscription->getReplacement().isUnspecified()) {
        if (unsubscription->getInview()) {
            remove_inview_entry(unsubscription->getLeaving());
        } else {
            parent->getParentModule()->getParentModule()->bubble(std::string("removed leaving ip ").append(unsubscription->getLeaving().getIp().str()).append("...").c_str());
            remove_mcache_entry(unsubscription->getLeaving());
        }
    } else {
        if (unsubscription->getInview()) {
            for (TransportAddress tad : inview) {
                if (tad == unsubscription->getReplacement()) return;
            }
            for (TransportAddress tad : inview) {
                if (tad == unsubscription->getLeaving()) {
                    tad = unsubscription->getReplacement();
                    return;
                }
            }
        } else {
            if (mcache_contains_tad(unsubscription->getReplacement())) return;
            for (mCacheEntry node : mCache) {
                if (node.tad == unsubscription->getLeaving()) {
                    parent->getParentModule()->getParentModule()->bubble(std::string("replaced leaving ip ").append(unsubscription->getLeaving().getIp().str())
                            .append(" with ").append(unsubscription->getReplacement().getIp().str()).append("...").c_str());
                    parent->deleteOverlayNeighborArrow(node.tad);
                    parent->showOverlayNeighborArrow(unsubscription->getReplacement(), false, "ls=red,1");
                    node.tad = unsubscription->getReplacement();
                    return;
                }
            }
        }
    }
}

// HEARTBEAT MESSAGES // UDP
// sent to nodes to inform that their neighbours are still alive.
// if no heartbeat is received in some time, a node will resubscribe
void MembershipManager::send_heartbeat_message(TransportAddress tad) {
    Heartbeat* heartbeat = new Heartbeat();
    parent->sendMessageToUDP(tad, heartbeat);
}
void MembershipManager::receive_heartbeat_message(Heartbeat* heartbeat) {
    setOrReplace(no_heartbeat_timer, "no_heartbeat_timer", scamp_heartbeat_failure_interval);
}
