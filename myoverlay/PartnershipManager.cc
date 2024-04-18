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

#include <algorithm>
#include "PartnershipManager.h"
#include "PartnerEntry.h"
#include "Node.h"
#include "common/TransportAddress.h"

// utility functions
#define setOrReplace(timer, name, offset) if (timer != NULL && timer->isScheduled()) { \
    parent->cancelEvent(timer); \
} else if (!timer) { \
    timer = new cMessage(name); \
} \
parent->scheduleAt(simTime() + offset, timer)

bool PartnershipManager::is_partner(TransportAddress tad) {
    for (PartnerEntry partner : partners) {
        if (partner.tad == tad) return true;
    }
    return false;
}

void PartnershipManager::insert_partner(TransportAddress partner) {
    if (is_partner(partner)) return;
    partners.push_back(PartnerEntry(partner));
    parent->set_arrow(partner, "PARTNER", true);
}

void PartnershipManager::insert_new_partner(TransportAddress partner) {
    if (is_partner(partner)) return;
    insert_partner(partner);
    send_partnership_message(partner);
}

void PartnershipManager::insert_new_partner_if_needed(TransportAddress tad) {
    if (partners.size() >= M) return;
    insert_new_partner(tad);
}

void PartnershipManager::remove_partner(TransportAddress partner) {
    for (auto i = partners.begin(); i != partners.end(); ++i) {
        if (i->tad == partner) {
            parent->set_arrow(i->tad, "PARTNER", false);
            partners.erase(i);
            return;
        }
    }
}

void PartnershipManager::remove_worst_scoring_partner() {
    auto erased = min_element(partners.begin(), partners.end());
    parent->set_arrow(erased->tad, "PARTNER", false);
    send_partnership_end_message(erased->tad);
    partners.erase(erased);
}

std::vector<TransportAddress> PartnershipManager::get_partner_tads() {
    std::vector<TransportAddress> tads;
    for (PartnerEntry partner : partners) {
        tads.push_back(partner.tad);
    }
    return tads;
}

// lifecycle
void PartnershipManager::init(Node* p, int si, int m) {
    parent = p;
    switch_interval = si;
    M = m;
}

void PartnershipManager::get_candidate_partners_from_deputy(TransportAddress deputy) {
    send_get_candidate_partners_message(deputy);
    parent->getParentModule()->getParentModule()->bubble("getting candidate partners...");
}

void PartnershipManager::take_new_partner(TransportAddress tad) {
    if (is_partner(tad)) return;
    while (partners.size() >= M) {
        // is this an optimization over the original? should it be random? Good Fuciing Luck finding Out!!
        remove_worst_scoring_partner();
    }
    insert_partner(tad);
}

void PartnershipManager::replace_partner_with_new(TransportAddress from, TransportAddress with) {
    for (auto i = partners.begin(); i != partners.end(); ++i) {
        if (i->tad == from) {
            parent->set_arrow(i->tad, "PARTNER", false);
            partners.erase(i);
            insert_new_partner(with);
        }
    } // else we just didn't have it. whatever i don't wcare !!
}

void PartnershipManager::score_and_switch(TransportAddress with) {
    remove_worst_scoring_partner();
    insert_new_partner(with);
    setOrReplace(switch_timer, "switch_timer", switch_interval);
}

// GET CANDIDATE PARTNERS MESSAGES // TCP
// get list of possible starting partners from the deputy
void PartnershipManager::send_get_candidate_partners_message(TransportAddress tad) {
    GetCandidatePartnersCall* get_candidate_partners_call = new GetCandidatePartnersCall();
    get_candidate_partners_call->setFrom(parent->getThisNode());
    parent->send_rpc(tad, get_candidate_partners_call);
}

void PartnershipManager::receive_get_candidate_partners_message_and_respond(GetCandidatePartnersCall* get_candidate_partners_call, std::vector<TransportAddress> from_mCache) {
    GetCandidatePartnersResponse* get_candidate_partners_response = new GetCandidatePartnersResponse();
    get_candidate_partners_response->setCandidates(from_mCache);
    parent->send_rpc_response(get_candidate_partners_call, get_candidate_partners_response);
}

void PartnershipManager::timeout_get_candidate_partners_response(GetCandidatePartnersCall* get_candidate_partners_call) {
    // we don't handle this here !! we handle this by getting a new deputy in the MembershipManager
}

void PartnershipManager::receive_get_candidate_partners_response(GetCandidatePartnersResponse* get_candidate_partners_response) {
    for (TransportAddress candidate : get_candidate_partners_response->getCandidates()) {
        // because of mcache gossiping and our addition of insert_new_partner_if_needed, we might already have partners by now
        if (partners.size() >= M) break;
        insert_new_partner(candidate);
    }
    setOrReplace(switch_timer, "switch_timer", switch_interval);
    parent->getParentModule()->getParentModule()->bubble(std::string("received ").append(std::to_string(partners.size())).append(" candidates...").c_str());
}

// PARTNERSHIP MESSAGES // UDP
// negotiate beginning a partnership with a node
void PartnershipManager::send_partnership_message(TransportAddress tad) {
    Partnership* partnership = new Partnership();
    partnership->setFrom(parent->getThisNode());
    parent->sendMessageToUDP(tad, partnership);
}

// we decide to always accept new partnerships, starting a chain of users being pushed from a single partnership
// until the system converges on stability, which happens at certain node intervals depending on M.
void PartnershipManager::receive_partnership_message(Partnership* partnership) {
    take_new_partner(partnership->getFrom());
}

// PARTNERSHIP ENDING MESSAGES // UDP
// cuts a partnership with a node cleanly
void PartnershipManager::send_partnership_end_message(TransportAddress tad) {
    PartnershipEnd* partnership_end = new PartnershipEnd();
    partnership_end->setFrom(parent->getThisNode());
    parent->sendMessageToUDP(tad, partnership_end);
}

void PartnershipManager::receive_partnership_end_message(PartnershipEnd* partnership_end, TransportAddress with) {
    replace_partner_with_new(partnership_end->getFrom(), with);
}

PartnershipManager::~PartnershipManager() {
    parent->cancelAndDelete(switch_timer);
}
