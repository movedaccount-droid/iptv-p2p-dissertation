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

#include <functional>
#include <iterator>
#include <random>
#include "PartnerlinkManager.h"
#include "Node.h"

// utility functions
#define setOrReplace(timer, name, offset) if (timer != NULL && timer->isScheduled()) { \
    parent->cancelEvent(timer); \
} else if (!timer) { \
    timer = new cMessage(name); \
} \
parent->scheduleAt(simTime() + offset, timer)

TransportAddress PartnerlinkManager::get_random_in(std::set<TransportAddress> set) {
    std::random_device ran;
    std::mt19937 rng(ran());

    if (set.size() == 0) throw "no address in set from which to pull random";

    auto it = set.begin();
    std::uniform_int_distribution<std::mt19937::result_type> random_index(0, set.size() - 1);
    std::advance(it, random_index(rng));
    return *it;
}

TransportAddress PartnerlinkManager::get_random_partner() {
    std::set<TransportAddress> all_partners;
    for (auto entry : partners) {
        all_partners.insert(entry.first);
    }
    return get_random_in(all_partners);
}

TransportAddress PartnerlinkManager::get_random_partner_matching_predicate(std::function<bool(std::pair<TransportAddress, bool>)> const& predicate) {
    std::set<TransportAddress> matching_partners;
    for (auto entry : partners) {
        if (predicate(entry)) {
            matching_partners.insert(entry.first);
        }
    }
    return get_random_in(matching_partners);
}

TransportAddress PartnerlinkManager::get_random_partner_with_exceptions(std::set<TransportAddress> exceptions) {
    std::set<TransportAddress> non_excepted_partners;
    for (auto entry : partners) {
        if (exceptions.find(entry.first) == exceptions.end()) {
            non_excepted_partners.insert(entry.first);
        }
    }
    return get_random_in(non_excepted_partners);
}

TransportAddress PartnerlinkManager::get_random_partner_with_panic_status(bool panicking) {
    std::set<TransportAddress> partners_matching_status;
    for (auto entry : partners) {
        if (entry.second == panicking) {
            partners_matching_status.insert(entry.first);
        }
    }
    return get_random_in(partners_matching_status);
}

// we adjust Mc in these following functions.
// you should manually track whatever your action SHOULD do to Mc,
// and these functions will automatically adjust if there are duplicate partners etc.

// i.e. failing a connection to timeout should reduce Mc by 1, so we call remove and Mc-- in sequence.
// if we somehow timeout a partner that we don't know, however,
// the reduce function will correct our value for us.

void PartnerlinkManager::insert_partner_to_partners(TransportAddress partner) {
    auto partner_entry = partners.find(partner);
    if (partner_entry != partners.end()) {
        Mc--; // we added a connection but already knew it
    } else {
        partners.insert({partner, false});
        parent->set_arrow(partner, "PARTNER", true);
        set_failure_timer(partner);
    }
}

void PartnerlinkManager::remove_partner_from_partners(TransportAddress partner) {
    auto partner_entry = partners.find(partner);
    if (partner_entry == partners.end()) {
        Mc++; // we removed a connection but didn't know it
    } else {
        partners.erase(partner);
        parent->set_arrow(partner, "PARTNER", false);
        remove_failure_timer(partner);
    }
}

bool PartnerlinkManager::is_timed_out(simtime_t origin_time, simtime_t timeout) {
    return simTime() - origin_time - timeout <= 0;
}

// lifecycle
void PartnerlinkManager::init(Node* p, int m, double pts) {
    parent = p;
    M = m;
    partnership_timeout = SimTime(pts, SIMTIME_S);
}

// failure timers and buffermap timeout
void PartnerlinkManager::set_failure_timer(TransportAddress partner) {
    Failure* failure = new Failure();
    failure->setFailed(partner);
    parent->scheduleAt(simTime() + partnership_timeout, failure);
    fail_connection_timers.insert({partner, failure});
}

void PartnerlinkManager::remove_failure_timer(TransportAddress partner) {
    parent->cancelAndDelete(fail_connection_timers[partner]);
    fail_connection_timers.erase(partner);
}

void PartnerlinkManager::reset_failure_timer(TransportAddress partner) {
    Failure* failure = fail_connection_timers[partner];
    parent->cancelEvent(failure);
    parent->scheduleAt(simTime() + partnership_timeout, failure);
}

void PartnerlinkManager::read_failure_timer_and_fail_connection(Failure* failure) {
    remove_partner_from_partners(failure->getFailed());
    Mc--;
}

// panic tracking
void PartnerlinkManager::check_panicking_status() {
    if (Mc == 0) {
        // that's not good.
        // TODO: how do we resolve this? zero-delay self-message caught by membership manager??
    }
    if ((Mc == M - 1 || Mc <= M - 3) && panic_timeout_timer == NULL) {
        // when this timer times out, we automatically send another message,
        // so we just check if the timer is already out
        panic_timeout_timer = new cMessage("panic message timed out");
        send_panic_message(get_random_partner(), parent->getThisNode());
    }
    if ((Mc == M - 2 || Mc <= M - 3) && panic_split_timeout_timer == NULL) {
        panic_timeout_timer = new cMessage("panicsplit message timed out");
        send_panic_split_message(get_random_partner());
    }
}

// GET CANDIDATE PARTNERS MESSAGES // TCP
// get list of possible starting partners from the deputy
void PartnerlinkManager::send_get_candidate_partners_message(TransportAddress tad) {
    GetCandidatePartnersCall* get_candidate_partners_call = new GetCandidatePartnersCall();
    get_candidate_partners_call->setFrom(parent->getThisNode());
    parent->send_rpc(tad, get_candidate_partners_call);
}

void PartnerlinkManager::receive_get_candidate_partners_message_and_respond(GetCandidatePartnersCall* get_candidate_partners_call, std::map<TransportAddress, double> from_mCache) {
    GetCandidatePartnersResponse* get_candidate_partners_response = new GetCandidatePartnersResponse();
    get_candidate_partners_response->setCandidates(from_mCache);
    parent->send_rpc_response(get_candidate_partners_call, get_candidate_partners_response);
}

// TODO: remove use of bandwidth ??? in here
void PartnerlinkManager::receive_get_candidate_partners_response(GetCandidatePartnersResponse* get_candidate_partners_response) {
    for (auto candidate : get_candidate_partners_response->getCandidates()) {
        send_split_message(candidate.first);
    }
    // TODO: we need to enable this eventually
    // setOrReplace(switch_timer, "switch_timer", switch_interval);
    parent->getParentModule()->getParentModule()->bubble(std::string("received ").append(std::to_string(partners.size())).append(" candidates...").c_str());
}

// SPLIT // TCP
// request a node to split a relationship with a partner, and put this node in the middle
void PartnerlinkManager::send_split_message(TransportAddress tad) {
    SplitCall* split_call = new SplitCall();
    split_call->setInto(parent->getThisNode());
    split_call->setUuid(rand());
    parent->send_rpc(tad, split_call);
}

void PartnerlinkManager::receive_split_message_and_try_split_with_partner(SplitCall* split_call) {
    if (partners.find(split_call->getInto()) == partners.end()) {
        SplitResponse* split_response = new SplitResponse();
        split_response->setResult(FAILED);
        parent->send_rpc_response(split_call, split_response);
    } else {
        // buffer and respond after we know how the split went
        send_try_split_message(get_random_partner(),
                split_call->getInto(),
                split_call->getUuid());
        currently_splitting.insert({split_call->getUuid(), split_call});
    }
}

void PartnerlinkManager::send_split_failure_response(SplitCall* split_call) {
    SplitResponse* split_response = new SplitResponse();
    split_response->setResult(FAILED);
    parent->send_rpc_response(split_call, split_response);
}

void PartnerlinkManager::receive_split_response(SplitResponse* split_response) {
    if (split_response->getResult() == SUCCESS) {
        // if we already know one of these, we start Panicking
        insert_partner_to_partners(split_response->getFirst_node());
        insert_partner_to_partners(split_response->getSecond_node());
    } else {
        Mc -= 2; // causing the node to start sending PanicSplits
    }
}
void PartnerlinkManager::timeout_split_response(SplitCall* split_call) {
    Mc -= 2; // causing the node to start sending PanicSplits
}

// TRY_SPLIT // TCP
// get a partner to check if we can split, and ask them to hook up with the new node if so
// after the response, if successful, we then wind down our side of the partnership and do the same
void PartnerlinkManager::send_try_split_message(TransportAddress tad, TransportAddress into, int uuid) {
    TrySplitCall* try_split_call = new TrySplitCall();
    try_split_call->setUuid(uuid);
    try_split_call->setInto(into);
    try_split_call->setFrom(parent->getThisNode());
    parent->send_rpc(tad, try_split_call);
}

void PartnerlinkManager::receive_try_split_message_and_try_split(TrySplitCall* try_split_call) {
    TrySplitResponse* try_split_response = new TrySplitResponse();
    try_split_response->setUuid(try_split_call->getUuid());
    if (partners.find(try_split_call->getInto()) != partners.end()
            || partners.find(try_split_call->getFrom()) == partners.end()) {
        try_split_response->setResult(FAILED);
    } else {
        remove_partner_from_partners(try_split_call->getFrom());
        insert_partner_to_partners(try_split_call->getInto());
        try_split_response->setResult(SUCCESS);
        try_split_response->setFrom(parent->getThisNode());
        try_split_response->setInto(try_split_call->getInto());
    }
    parent->send_rpc_response(try_split_call, try_split_response);
}

void PartnerlinkManager::receive_try_split_response(TrySplitResponse* try_split_response) {

    // we could by now already be partners with the new node. in that case our old partner has already
    // connected to it, but we and the new node will be down a connection, so we both end up in panic.
    // still, this is the best outcome in this case - no way to revert the old partnership - so we allow it to happen.
    // we could also by some miserable outcome no longer be partners with our splitting partner.
    // the implications of this are difficult to trace, so we simply fail the request and let the
    // two old partnered nodes panic, which is at least consistent and will not introduce any new links to the network.

    SplitCall* split_call = currently_splitting[try_split_response->getUuid()];
    if (partners.find(try_split_response->getFrom()) == partners.end()
            || try_split_response->getResult() == FAILED) {
        send_split_failure_response(split_call);
    } else {
        remove_partner_from_partners(try_split_response->getFrom());
        insert_partner_to_partners(try_split_response->getInto());
        SplitResponse* split_response = new SplitResponse();
        split_response->setResult(SUCCESS);
        split_response->setFirst_node(parent->getThisNode());
        split_response->setSecond_node(try_split_response->getFrom());
        parent->send_rpc_response(split_call, split_response);
    }
}
void PartnerlinkManager::timeout_try_split_response(TrySplitCall* try_split_call) {
    SplitCall* split_call = currently_splitting[try_split_call->getUuid()];
    send_split_failure_response(split_call);
}

// PANIC // UDP
// gossip a message looking for another panicking node we do not know, recovering one link to our node if found
void PartnerlinkManager::send_panic_message(TransportAddress tad, TransportAddress panicking) {
    Panic* panic = new Panic();
    panic->setPanicking(panicking);
    panic->setSend_time(simTime());
    parent->sendMessageToUDP(tad, panic);
}

void PartnerlinkManager::receive_panic_message(Panic* panic) {
    if (panic_timeout_timer == NULL
            || parent->getThisNode() == panic->getPanicking()
            || partners.find(panic->getPanicking()) != partners.end()) {
        // we know the node or are not panicking, forward further
        TransportAddress random_partner;
        try {
            auto partner_with_panic_status = [=](std::pair<const TransportAddress, bool> pair) {
                return pair.second == true && pair.first != panic->getLast_hop() && pair.first != panic->getPanicking();
            };
            random_partner = get_random_partner_matching_predicate(partner_with_panic_status);
        } catch (const char* c) {
            try {
                auto not_return_path = [=](std::pair<const TransportAddress, bool> pair) {
                    return pair.first != panic->getLast_hop() && pair.first != panic->getPanicking();
                };
                random_partner = get_random_partner_matching_predicate(not_return_path);
            } catch (const char* c) {
                try {
                    random_partner = get_random_partner();
                } catch (const char* c) {
                    // well that sucks
                    return;
                }
            }
        }
        send_panic_message(random_partner, panic->getPanicking());
    } else {
        // TODO: accept panic
    }
}

PartnerlinkManager::PartnerlinkManager() {
    panic_timeout_timer = NULL;
    panic_split_timeout_timer = NULL;
}

PartnerlinkManager::~PartnerlinkManager() {
    if (panic_timeout_timer != NULL) parent->cancelAndDelete(panic_timeout_timer);
    if (panic_split_timeout_timer != NULL) parent->cancelAndDelete(panic_split_timeout_timer);
}

