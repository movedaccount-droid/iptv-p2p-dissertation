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

#include "../coolstreaming/PartnershipManager.h"

#include <algorithm>
#include <iterator>

#include "../coolstreaming/Node.h"
#include "../coolstreaming/PartnerEntry.h"
#include "common/TransportAddress.h"

// utility functions
#define setOrReplace(timer, name, offset) if (timer != NULL && timer->isScheduled()) { \
    parent->cancelEvent(timer); \
} else if (!timer) { \
    timer = new cMessage(name); \
} \
parent->scheduleAt(simTime() + offset, timer)

void PartnershipManager::insert_partner(TransportAddress partner, double bandwidth) {
    if (partners.find(partner) != partners.end()) return;
    partners.insert({partner, PartnerEntry(bandwidth)});
    if (parent->origin) partner_k.push_back(partner);
    parent->set_arrow(partner, "PARTNER", true);
}

void PartnershipManager::insert_new_partner(TransportAddress partner, double bandwidth) {
    if (partners.find(partner) != partners.end()) return;
    send_partnership_message(partner);
    insert_partner(partner, bandwidth);
}

void PartnershipManager::insert_new_partner_if_needed(TransportAddress tad, double bandwidth) {
    if (partners.size() < M) insert_new_partner(tad, bandwidth);
}

void PartnershipManager::erase_partner(TransportAddress tad) {
    partners.erase(tad);
    if (parent->origin) {
        for (auto it = partner_k.begin(); it != partner_k.end(); ++it) {
            if (*it == tad) partner_k.erase(it); break;
        }
    }
    parent->set_arrow(tad, "PARTNER", false);
}

void PartnershipManager::remove_worst_scoring_partner() {
    typedef typename decltype(partners)::value_type& Comp;
    auto erased = min_element(partners.begin(), partners.end(),
            [](Comp l, Comp r) -> bool { return l.second < r.second;});
    parent->set_arrow(erased->first, "PARTNER", false);
    send_partnership_end_message(erased->first);
    // everything involving this thing is gross actually
    if (parent->origin) {
        for (auto it = partner_k.begin(); it != partner_k.end(); ++it) {
            if (*it == erased->first) partner_k.erase(it); break;
        }
    }
    partners.erase(erased);
}

std::set<TransportAddress> PartnershipManager::get_partner_tads() {
    std::set<TransportAddress> tads;
    for (auto entry : partners) {
        tads.insert(entry.first);
    }
    return tads;
}

std::map<TransportAddress, PartnerEntry> PartnershipManager::get_partners() {
    return partners;
}

std::vector<TransportAddress> PartnershipManager::get_partner_k() {
    return partner_k;
}

// lifecycle
void PartnershipManager::init(Node* p, double b, int si, int m) {
    parent = p;
    bandwidth = b;
    switch_interval = si;
    M = m;
}

void PartnershipManager::get_candidate_partners_from_deputy(TransportAddress deputy) {
    send_get_candidate_partners_message(deputy);
    parent->getParentModule()->getParentModule()->bubble("getting candidate partners...");
}

void PartnershipManager::take_new_partner(TransportAddress tad, double bandwidth) {
    if (partners.find(tad) != partners.end()) return;
    while (partners.size() >= M) {
        // is this an optimization over the original? should it be random? Good Fuciing Luck finding Out!!
        remove_worst_scoring_partner();
    }
    insert_partner(tad, bandwidth);
}

void PartnershipManager::replace_partner_with_new(TransportAddress from, TransportAddress with, double with_bandwidth) {
    erase_partner(from);
    insert_new_partner(with, with_bandwidth);
}

void PartnershipManager::score_and_switch(TransportAddress with, double with_bandwidth) {
    remove_worst_scoring_partner();
    insert_new_partner(with, with_bandwidth);
    setOrReplace(switch_timer, "switch_timer", switch_interval);
}

void PartnershipManager::reset_switch_timer() {
    setOrReplace(switch_timer, "switch_timer", switch_interval);
}

// GET CANDIDATE PARTNERS MESSAGES // TCP
// get list of possible starting partners from the deputy
void PartnershipManager::send_get_candidate_partners_message(TransportAddress tad) {
    GetCandidatePartnersCall* get_candidate_partners_call = new GetCandidatePartnersCall();
    get_candidate_partners_call->setFrom(parent->getThisNode());
    parent->send_rpc(tad, get_candidate_partners_call);
}

void PartnershipManager::receive_get_candidate_partners_message_and_respond(GetCandidatePartnersCall* get_candidate_partners_call, std::map<TransportAddress, double> from_mCache) {
    GetCandidatePartnersResponse* get_candidate_partners_response = new GetCandidatePartnersResponse();
    get_candidate_partners_response->setCandidates(from_mCache);
    parent->send_rpc_response(get_candidate_partners_call, get_candidate_partners_response);
}

void PartnershipManager::timeout_get_candidate_partners_response(GetCandidatePartnersCall* get_candidate_partners_call) {
    // we don't handle this here !! we handle this by getting a new deputy in the MembershipManager
}

void PartnershipManager::receive_get_candidate_partners_response(GetCandidatePartnersResponse* get_candidate_partners_response) {
    for (auto candidate : get_candidate_partners_response->getCandidates()) {
        // because of mcache gossiping and our addition of insert_new_partner_if_needed, we might already have partners by now
        if (partners.size() >= M) break;
        insert_new_partner(candidate.first, candidate.second);
    }
    setOrReplace(switch_timer, "switch_timer", switch_interval);
    parent->getParentModule()->getParentModule()->bubble(std::string("received ").append(std::to_string(partners.size())).append(" candidates...").c_str());
}

// PARTNERSHIP MESSAGES // UDP
// negotiate beginning a partnership with a node
void PartnershipManager::send_partnership_message(TransportAddress tad) {
    Partnership* partnership = new Partnership();
    partnership->setFrom(parent->getThisNode());
    partnership->setBandwidth(bandwidth);
    parent->sendMessageToUDP(tad, partnership);
}

// we decide to always accept new partnerships, starting a chain of users being pushed from a single partnership
// until the system converges on stability, which happens at certain node intervals depending on M.
void PartnershipManager::receive_partnership_message(Partnership* partnership) {
    take_new_partner(partnership->getFrom(), partnership->getBandwidth());
}

// PARTNERSHIP ENDING MESSAGES // UDP
// cuts a partnership with a node cleanly
void PartnershipManager::send_partnership_end_message(TransportAddress tad) {
    PartnershipEnd* partnership_end = new PartnershipEnd();
    partnership_end->setFrom(parent->getThisNode());
    parent->sendMessageToUDP(tad, partnership_end);
}

void PartnershipManager::receive_partnership_end_message(PartnershipEnd* partnership_end, TransportAddress with, double with_bandwidth) {
    replace_partner_with_new(partnership_end->getFrom(), with, with_bandwidth);
}

void PartnershipManager::receive_buffer_map_message(BufferMap* buffer_map) {
    auto partner = partners.find(buffer_map->getFrom());
    if (partner != partners.end()) {
        partner->second.buffer_map = buffer_map->getBuffer_map();
    }
}

PartnershipManager::~PartnershipManager() {
    parent->cancelAndDelete(switch_timer);
}
