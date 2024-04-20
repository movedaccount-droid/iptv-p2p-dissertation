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

#include "../coolstreaming/MembershipManager.h"

#include <algorithm>
#include <cstdlib>
#include <random>
#include <vector>

#include "../coolstreaming/Coolstreaming_m.h"
#include "../coolstreaming/mCacheEntry.h"
#include "../coolstreaming/Node.h"

// utility functions
#define setOrReplace(timer, name, offset) if (timer != NULL && timer->isScheduled()) { \
    parent->cancelEvent(timer); \
} else if (!timer) { \
    timer = new cMessage(name); \
} \
parent->scheduleAt(simTime() + offset, timer)

std::pair<const TransportAddress, mCacheEntry> MembershipManager::random_mcache_entry(TransportAddress exclude) {

    std::random_device ran;
    std::mt19937 rng(ran());

    int empty_size = exclude.isUnspecified() ? 0 : 1;

    while (mCache.size() > empty_size) {
        std::uniform_int_distribution<std::mt19937::result_type> random_index(0, mCache.size() - 1);
        auto it = mCache.begin();
        std::advance(it, random_index(rng));
        if (it->second.expired()) {
            parent->getParentModule()->getParentModule()->bubble(std::string("expired random ip ").append(it->first.getIp().str()).append("...").c_str());
            mCache.erase(it);
        } else if (exclude.isUnspecified() || it->first != exclude) {
            return *it;
        }
    }

    throw "no entries in cache";

}

std::pair<const TransportAddress, mCacheEntry> MembershipManager::random_mcache_entry(std::set<TransportAddress> exclude) {

    std::random_device ran;
    std::mt19937 rng(ran());

    int empty_size = exclude.size();

    while (mCache.size() > empty_size) {
        std::uniform_int_distribution<std::mt19937::result_type> random_index(0, mCache.size() - 1);
        auto it = mCache.begin();
        std::advance(it, random_index(rng));
        if (it->second.expired()) {
            parent->getParentModule()->getParentModule()->bubble(std::string("expired random ip ").append(it->first.getIp().str()).append("...").c_str());
            mCache.erase(it);
        } else if (exclude.find(it->first) == exclude.end()) {
            return *it;
        }
    }

    throw "no entries in cache";

}

std::map<TransportAddress, double> MembershipManager::get_partner_candidates(TransportAddress exclude, int this_node_partner_count) {

    std::random_device ran;
    std::mt19937 rng(ran());

    const int EMPTY_SIZE = 1;
    std::map<TransportAddress, double> candidates;

    // we do this the Kind of Nasty way. build vec shuffle and pull values
    std::vector<TransportAddress> all;
    for (auto entry : mCache) {
        all.push_back(entry.first);
    }
    std::shuffle(all.begin(), all.end(), rng);

    while (all.size() > EMPTY_SIZE && candidates.size() < M) {
        std::uniform_int_distribution<std::mt19937::result_type> random_index(0, all.size() - 1);
        auto it = all.begin();
        std::advance(it, random_index(rng));
        if (mCache.at(*it).expired()) {
            parent->getParentModule()->getParentModule()->bubble(std::string("expired random ip ").append(it->getIp().str()).append("...").c_str());
            mCache.erase(*it);
        } else if (*it != exclude) {
            candidates.insert({*it, mCache.at(*it).bandwidth});
        }
        all.erase(it);
    }

    if (candidates.size() < M && this_node_partner_count < M) candidates.insert({parent->getThisNode(), bandwidth});

    return candidates;

}

void MembershipManager::insert_mcache_entry(TransportAddress tad, int seq_num, int num_partner, simtime_t ttl, double bandwidth) {
    if (mCache.find(tad) != mCache.end()) return;
    mCacheEntry insert(seq_num, num_partner, ttl, bandwidth);
    if (!insert.expired()) {
        mCache.insert({tad, insert});
        parent->set_arrow(tad, "MCACHE", true);
    }
}

void MembershipManager::remove_mcache_entry(TransportAddress tad) {
    auto entry = mCache.find(tad);
    if (entry != mCache.end()) {
        mCache.erase(entry);
        parent->set_arrow(entry->first, "MCACHE", false);
    }
}

// init
void MembershipManager::init(Node* p, TransportAddress ot, double b, int cin, int scr, int sch, int schf, int m) {
    parent = p;
    origin_tad = ot;
    bandwidth = b;
    c = cin;
    scamp_resubscription_interval = scr;
    scamp_heartbeat_interval = sch;
    scamp_heartbeat_failure_interval = schf;
    M = m;
}

void MembershipManager::join_overlay() {
    setOrReplace(resubscription_timer, "resubscription_timer", scamp_resubscription_interval);
    setOrReplace(send_heartbeat_timer, "send_heartbeat_timer", scamp_heartbeat_interval);
    setOrReplace(no_heartbeat_timer, "no_heartbeat_timer", scamp_heartbeat_failure_interval);
    if (!parent->origin) {
        send_get_deputy_message(origin_tad);
    }
    parent->getParentModule()->getParentModule()->bubble("joining...");
}

void MembershipManager::contact_deputy_and_enter_network(TransportAddress deputy) {
    send_entry_membership_message(deputy);
    parent->getParentModule()->getParentModule()->bubble("contacting deputy...");
}

void MembershipManager::resubscribe() {
    inview = std::set<TransportAddress>();
    setOrReplace(resubscription_timer, "resubscription_timer", scamp_resubscription_interval);
    try {
        send_membership_message(random_mcache_entry().first);
        parent->getParentModule()->getParentModule()->bubble("resubscribing...");
    } catch (const char* c) {
        send_get_deputy_message(origin_tad);
        EV << "[MembershipManager::resubscribe() @ " << parent->getThisNode().getIp() << "]\n"
           << "    attempted to resubscribe but had empty partial view, reentering at origin..."
           << endl;
        parent->getParentModule()->getParentModule()->bubble("reentering from origin...");
    }
}

void MembershipManager::unsubscribe() {
    auto ic = mCache.begin();
    auto ii = inview.begin();
    if (ic != mCache.end()) {
        for (int i = 1; i <= static_cast<int>(inview.size()) - c - 1; ++i) {
            send_unsubscribe_message(*ii, false, ic->first);
            send_unsubscribe_message(ic->first, true, *ii);
            ++ii; ++ic;
            if (ic == mCache.end()) ic = mCache.begin();
        }
    }
    while (ii != inview.end()) {
        send_unsubscribe_message(*ii, false);
        ++ii;
    }
}

void MembershipManager::gossip_and_unsubscribe_failed_partner(TransportAddress failing) {
    for (auto entry : mCache) {
        send_gossiped_unsubscribe_message(entry.first, failing);
    }
}

void MembershipManager::send_heartbeats() {
    for (auto entry : mCache) {
        send_heartbeat_message(entry.first);
    }
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
    unsubscribe();
    parent->cancelAndDelete(resubscription_timer);
    parent->cancelAndDelete(send_heartbeat_timer);
    parent->cancelAndDelete(no_heartbeat_timer);
    parent = NULL;
}

// GET DEPUTY MESSAGES // TCP
// gets deputy from origin node
void MembershipManager::send_get_deputy_message(TransportAddress tad) {
    GetDeputyCall* get_deputy_call = new GetDeputyCall();
    parent->send_rpc(tad, get_deputy_call);
}

void MembershipManager::receive_get_deputy_message_and_respond(GetDeputyCall* get_deputy_call, int block_index) {
    if (!parent->origin) {
        EV << "[MembershipManager::receive_get_deputy_message_and_respond() @ " << parent->getThisNode().getIp() << "]\n"
           << "    node that was not an origin took a GetDeputy message ????"
           << endl;
        parent->getParentModule()->getParentModule()->bubble("[???] received GETDEPUTY when not deputy");
        return;
    }
    GetDeputyResponse* get_deputy_response = new GetDeputyResponse();
    try {
        get_deputy_response->setDeputy(random_mcache_entry().first);
    } catch (const char* c) {
        get_deputy_response->setDeputy(parent->getThisNode());
    }
    get_deputy_response->setBlock_index(block_index);
    parent->send_rpc_response(get_deputy_call, get_deputy_response);
}

void MembershipManager::timeout_get_deputy_response(GetDeputyCall* get_deputy_call) {
    EV << "[MembershipManager::receive_get_deputy_message_and_respond() @ " << parent->getThisNode().getIp() << "]\n"
       << "    timed out when contacting origin node for deputy, retrying..."
       << endl;
    parent->getParentModule()->getParentModule()->bubble("timed out on GetDeputy, retrying...");
    send_get_deputy_message(origin_tad);
}

void MembershipManager::receive_get_deputy_response(GetDeputyResponse* get_deputy_response) {
    contact_deputy_and_enter_network(get_deputy_response->getDeputy());
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
    membership->setBandwidth(bandwidth);
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
    insert_mcache_entry(membership->getTad(),
            membership->getSeq_num(),
            membership->getNum_partner(),
            membership->getTtl(),
            membership->getBandwidth());
    generate_inview_message(membership->getTad());
}

// returns if mcache entry was accepted, so we shortcircuit partnershipmanager behaviour later
bool MembershipManager::receive_membership_message(Membership* membership) {
    if (!membership->getForwarded()) {
        if (mCache.size() == 0 && parent->origin) {
            // special case if we are the origin
            // so that we are always outputting video Somewhere
            parent->getParentModule()->getParentModule()->bubble("origin had no mcache, forced bar with node...");
            absorb_membership_message(membership);
            send_forced_membership_message(membership->getTad());
            return true;
        }
        // algorithm 1: forward to all nodes of view
        int c = 0;
        for (auto entry : mCache) {
            if (entry.second.expired()) {
                parent->getParentModule()->getParentModule()->bubble(std::string("expired forwarding ip ").append(entry.first.getIp().str()).append("...").c_str());
                remove_mcache_entry(entry.first);
                continue;
            }
            if (entry.first == membership->getTad()) continue;
            forward_membership_message(membership, entry.first);
            c++;
        };
        parent->getParentModule()->getParentModule()->bubble(std::string("FF'd to ").append(std::to_string(c)).append(" base nodes...").c_str());
        for (int j = 0; j < c; ++j) {
            try {
                forward_membership_message(membership, random_mcache_entry().first);
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
        return false;
    } else {
        // drop if seen too many times
        auto seenCount = uuidCounts.find(membership->getUuid());
        if (seenCount != uuidCounts.end()) {
            if (seenCount->second > 10) {
                parent->getParentModule()->getParentModule()->bubble("dropped message...");
                return false;
            }
            uuidCounts[membership->getUuid()] = seenCount->second + 1;
        } else {
            uuidCounts.insert(std::make_pair(membership->getUuid(), 1));
        }
        // algorithm 2: add to cache or further forward
        double p = 1/(1 + mCache.size());
        bool success = rand() / RAND_MAX <= p;
        if (success && mCache.find(membership->getTad()) == mCache.end()) {
            absorb_membership_message(membership);
            parent->getParentModule()->getParentModule()->bubble("absorbed message...");
            return true;
        } else {
            try {
                forward_membership_message(membership, random_mcache_entry(membership->getTad()).first);
                parent->getParentModule()->getParentModule()->bubble("forwarded message...");
            } catch (const char* c) {
                EV << "[MembershipManager::receive_membership_message() @ " << parent->getThisNode().getIp() << "]\n"
                   << "    attempted to forward membership message but had nobody to forward to, dropping..."
                   << endl;
            }
            return false;
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
    inview.insert(inview_call->getAccepting_node());
    InviewResponse* inview_ack = new InviewResponse();
    parent->send_rpc_response(inview_call, inview_ack);
}

void MembershipManager::timeout_inview_ack(InviewCall* inview_call) {
    inview.erase(inview_call->getDestination());
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
    TransportAddress leaving = unsubscription->getLeaving();
    TransportAddress replacement = unsubscription->getReplacement();
    bool for_inview = unsubscription->getInview();
    if (replacement.isUnspecified()) {
        if (for_inview) {
            inview.erase(leaving);
        } else {
            parent->getParentModule()->getParentModule()->bubble(std::string("removed leaving ip ").append(leaving.getIp().str()).append("...").c_str());
            remove_mcache_entry(leaving);
        }
    } else {
        if (for_inview) {
            inview.erase(leaving);
            inview.insert(replacement);
        } else {
            auto old = mCache.find(leaving);
            if (old == mCache.end()) return;
            // if we already know the new node, we should assume their own entry is more accurate
            if (mCache.find(replacement) == mCache.end()) {
                mCache.insert({replacement, old->second});
                parent->set_arrow(replacement, "MCACHE", true);
            }
            parent->getParentModule()->getParentModule()->bubble(std::string("replaced leaving ip ").append(leaving.getIp().str())
                    .append(" with ").append(replacement.getIp().str()).append("...").c_str());
            remove_mcache_entry(leaving);
        }
    }
}

// GOSSIPED UNSUBSCRIBE MESSAGES // UDP
// . okay. . Sent on Behalf of Failing Nodes when there has been no BM or Packet Transfer ???? in the . partner manager?? and no the fucking.  the fucking mcache???/
// and Gossiped Similarly to SCAMP ?????????? What the fuck are you talking about
void MembershipManager::send_gossiped_unsubscribe_message(TransportAddress tad, TransportAddress failing) {
    GossipedUnsubscription* gossiped_unsubscription = new GossipedUnsubscription();
    gossiped_unsubscription->setFailing(failing);
    gossiped_unsubscription->setFrom(parent->getThisNode());
    parent->sendMessageToUDP(tad, gossiped_unsubscription);
}

void MembershipManager::receive_gossiped_unsubscribe_message(GossipedUnsubscription* gossiped_unsubscription) {
    // algorithm 2: add to cache or further forward. Simila r To. Similar To. Similar To.
    double p = 1 - 1/(1 + mCache.size());
    bool success = rand() / RAND_MAX <= p;
    if (success) {
        remove_mcache_entry(gossiped_unsubscription->getFailing());
        parent->getParentModule()->getParentModule()->bubble("dropped gossiped failing node...");
    } else {
        try {
            send_gossiped_unsubscribe_message(random_mcache_entry(gossiped_unsubscription->getFrom()).first, gossiped_unsubscription->getFailing());
            parent->getParentModule()->getParentModule()->bubble("forwarded gossiped failure message...");
        } catch (const char* c) {
            EV << "[MembershipManager::receive_gossiped_unsubscribe_message() @ " << parent->getThisNode().getIp() << "]\n"
               << "    attempted to forward gossiped failure message but had nobody to forward to, dropping..."
               << endl;
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
