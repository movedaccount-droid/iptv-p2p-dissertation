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

// lifecycle
void PartnershipManager::init(Node* p, int bmei, int m) {
    parent = p;
    bm_exchange_interval = bmei;
    M = m;
}

void PartnershipManager::get_candidate_partners_from_deputy(TransportAddress deputy) {
    send_get_candidate_partners_message(deputy);
    parent->getParentModule()->getParentModule()->bubble("getting candidate partners...");
}

void PartnershipManager::take_new_partner(TransportAddress tad) {
    while (partners.size() >= M) {
        partners.erase(min_element(partners.begin(), partners.end()));
    }
    partners.push_back(PartnerEntry(tad));
}

void PartnershipManager::replace_partner_with_new(TransportAddress from, TransportAddress with) {
    for (auto i = partners.begin(); i != partners.end(); ++i) {
        if (i->tad == from) {
            partners.erase(i);
            partners.push_back(PartnerEntry(with));
            send_partnership_message(with);
        }
    } // else we just didn't have it. whatever i don't wcare !!
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
        send_partnership_message(candidate);
    }
    setOrReplace(exchange_timer, "exchange_timer", 5);
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
    // TODO: remember to use exclude when getting the partner so that we don't
    // immiediately resucvbscribe oth the nasmae node
    replace_partner_with_new(partnership->getFrom(), with);
}

PartnershipManager::~PartnershipManager() {
    parent->cancelAndDelete(exchange_timer);
}
