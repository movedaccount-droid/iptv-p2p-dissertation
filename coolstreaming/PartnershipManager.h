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

#ifndef OVERLAY_COOLSTREAMING_PARTNERSHIPMANAGER_H_
#define OVERLAY_COOLSTREAMING_PARTNERSHIPMANAGER_H_

#include <vector>

#include "../coolstreaming/Coolstreaming_m.h"
#include "../coolstreaming/PartnerEntry.h"
#include "common/TransportAddress.h"

class Node;
class PartnershipManager {
public:
    Node* parent; // object structure ....
    std::vector<PartnerEntry> partners; // currently active partners
    int switch_interval; // between trying out a new partner from mcache
    int M; // target number of partners

    cMessage* switch_timer;

    // lifecycle
    void init(Node* p, int bmei, int m);
    void get_candidate_partners_from_deputy(TransportAddress deputy);
    void take_new_partner(TransportAddress tad);
    void replace_partner_with_new(TransportAddress from, TransportAddress with);
    void score_and_switch(TransportAddress with);

    // utils
    bool is_partner(TransportAddress tad);
    void insert_partner(TransportAddress partner);
    void insert_new_partner(TransportAddress partner);
    void insert_new_partner_if_needed(TransportAddress partner);
    void remove_partner(TransportAddress partner);
    void remove_worst_scoring_partner();
    std::vector<TransportAddress> get_partner_tads();

    // GET CANDIDATE PARTNERS MESSAGES // TCP
    // get list of possible starting partners from the deputy
    void send_get_candidate_partners_message(TransportAddress tad);
    void receive_get_candidate_partners_message_and_respond(GetCandidatePartnersCall* get_candidate_partners_call, std::vector<TransportAddress> from_mCache);
    void timeout_get_candidate_partners_response(GetCandidatePartnersCall* get_candidate_partners_call);
    void receive_get_candidate_partners_response(GetCandidatePartnersResponse* get_candidate_partners_response);

    // PARTNERSHIP MESSAGES // UDP
    // beginning a partnership with a node
    void send_partnership_message(TransportAddress tad);
    void receive_partnership_message(Partnership* partnership);

    // PARTNERSHIP ENDING MESSAGES // UDP
    // cuts a partnership with a node cleanly
    void send_partnership_end_message(TransportAddress tad);
    void receive_partnership_end_message(PartnershipEnd* partnership_end, TransportAddress with);

    PartnershipManager() { switch_timer = NULL; };
    virtual ~PartnershipManager();
};

#endif /* OVERLAY_COOLSTREAMING_PARTNERSHIPMANAGER_H_ */
