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

#ifndef OVERLAY_COOLSTREAMING_PARTNERLINKMANAGER_H_
#define OVERLAY_COOLSTREAMING_PARTNERLINKMANAGER_H_

#include <functional>
#include "TransportAddress.h"
#include "Coolstreaming_m.h"

class Node;
class PartnerlinkManager {
public:
    Node* parent;

    // params
    int M; // target number of partners
    simtime_t partnership_timeout; // duration without receiving buffermaps before a partner connection is failed
    simtime_t panic_timeout; // time-to-live for panic messages traversing the network
    simtime_t panic_split_timeout; // time-to-live for panicsplit messages traversing the network

    // vars
    std::map<TransportAddress, bool> partners; // map of partners and their panicking status
    std::map<int, SplitCall*> currently_splitting; // maps uuids to the message that requested the split, so we can respond via rpc_send_response later
    std::map<TransportAddress, Failure*> fail_connection_timers; // timers to fail a partner if we stop receiving buffermaps
    int Mc; // current number of partners. note that this is not the size of the partners set - ex. when we first join, this will be M, whilst partners.size() is 0.
            // you could also think of this as the "potential" number of partners, if everything resolves nicely excluding panic messages

    // timers
    cMessage* panic_timeout_timer; // the ttl on our panic has passed; send a new panic
    cMessage* panic_split_timeout_timer; // sama panicsplit

    // utility functions
    TransportAddress get_random_in(std::set<TransportAddress> set);
    TransportAddress get_random_partner();
    TransportAddress get_random_partner_matching_predicate(std::function<bool(std::pair<TransportAddress, bool>)> const& lambda);
    TransportAddress get_random_partner_with_exceptions(std::set<TransportAddress> exceptions);
    TransportAddress get_random_partner_with_panic_status(bool panicking);
    void insert_partner_to_partners(TransportAddress partner);
    void remove_partner_from_partners(TransportAddress partner);
    bool is_timed_out(simtime_t origin_time, simtime_t timeout);

    // lifecycle
    void init(Node* p, int m, double pts);

    // failure timers and buffermap timeout
    void set_failure_timer(TransportAddress partner);
    void remove_failure_timer(TransportAddress partner);
    void reset_failure_timer(TransportAddress partner);
    void read_failure_timer_and_fail_connection(Failure* failure);

    // panic tracking
    void check_panicking_status();

    // GET CANDIDATE PARTNERS // TCP
    // get list of possible starting partners from the deputy
    // timeout is handled by getting a new deputy in the MembershipManager
    void send_get_candidate_partners_message(TransportAddress tad);
    // TODO: remove the bandwidth from this when we can replace PartnershipManager
    void receive_get_candidate_partners_message_and_respond(GetCandidatePartnersCall* get_candidate_partners_call, std::map<TransportAddress, double> from_mCache);
    void receive_get_candidate_partners_response(GetCandidatePartnersResponse* get_candidate_partners_response);

    // SPLIT // TCP
    // request a node to split a relationship with a partner, and put this node in the middle
    void send_split_message(TransportAddress tad);
    void receive_split_message_and_try_split_with_partner(SplitCall* split_call);
    void send_split_failure_response(SplitCall* split_call);
    void receive_split_response(SplitResponse* split_response);
    void timeout_split_response(SplitCall* split_call);

    // TRY_SPLIT // TCP
    // get a partner to check if we can split, and ask them to hook up with the new node if so
    // after the response, if successful, we then wind down our side of the partnership and do the same
    void send_try_split_message(TransportAddress tad, TransportAddress into, int uuid);
    void receive_try_split_message_and_try_split(TrySplitCall* try_split_call);
    void receive_try_split_response(TrySplitResponse* try_split_response);
    void timeout_try_split_response(TrySplitCall* try_split_call);

    // PANIC // UDP
    // gossip a message looking for another panicking node we do not know, recovering one link to our node if found
    void send_panic_message(TransportAddress tad, TransportAddress panicking);
    void receive_panic_message(Panic* panic);

    // RECOVER // UDP
    // tell a panicking partner we are willing to take up one of its missing partnerships
    void send_recover_message(TransportAddress tad);
    void receive_recover_message(Recover* recover); // make sure in here that if M == Mc, we ignore the message

    PartnerlinkManager();
    virtual ~PartnerlinkManager();
};

#endif /* OVERLAY_COOLSTREAMING_PARTNERLINKMANAGER_H_ */
