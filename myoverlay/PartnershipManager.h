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

#ifndef OVERLAY_MYOVERLAY_PARTNERSHIPMANAGER_H_
#define OVERLAY_MYOVERLAY_PARTNERSHIPMANAGER_H_

#include <vector>
#include "common/TransportAddress.h"
#include "Coolstreaming_m.h"
#include "PartnerEntry.h"

class Node;
class PartnershipManager {
    Node* parent; // object structure ....
    std::vector<PartnerEntry> partners; // currently active partners
    int bm_exchange_interval; // seconds between buffermap sends
    int M; // target number of partners

    cMessage* exchange_timer;

public:
    // lifecycle
    void init(Node* p, int bmei, int m);
    void get_candidate_partners_from_deputy(TransportAddress deputy);
    void take_new_partner(TransportAddress tad);

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
    void receive_partnership_end_message(PartnershipEnd* partnership_end);

    PartnershipManager() { exchange_timer = NULL; };
    virtual ~PartnershipManager();
};

#endif /* OVERLAY_MYOVERLAY_PARTNERSHIPMANAGER_H_ */
