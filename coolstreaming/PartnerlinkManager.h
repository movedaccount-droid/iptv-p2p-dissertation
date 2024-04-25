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
#include "PartnerlinkEntry.h"
#include "Coolstreaming_m.h"

class Node;

// status enum
enum PanicStatus {
    Nominal,
    Panic,
    PanicSplit,
    PanicBoth,
    TotalFailure
};

class PartnerlinkManager {
public:
    Node* parent;

    // params
    int M; // target number of partners
    simtime_t partnership_timeout; // duration without receiving buffermaps before a partner connection is failed
    simtime_t panic_timeout; // time-to-live for panic messages traversing the network
    simtime_t panic_split_timeout; // time-to-live for panicsplit messages traversing the network
    simtime_t switch_interval; // time between switching to a new random peer from our mcache
    bool needs_deputy; // if we would like to be informed of deputies from any next get_deputies response
    int substream_count; // to build the default partnerlinkentry
    int tp; // constant for maximum gap between a node's partners
    bool display_string; // if to show partnerlink_manager display strings

    // vars
    std::string display_name; // used to set display name to Mc
    std::map<TransportAddress, PartnerlinkEntry> partners; // map of partners and relevant stats
    std::map<int, SplitCall*> currently_splitting; // maps uuids to the message that requested the split, so we can respond via rpc_send_response later
    std::map<TransportAddress, Failure*> fail_connection_timers; // timers to fail a partner if we stop receiving buffermaps
    std::set<int> active_switch_messages; // uuids assocated with any mCache-switching Split messages we have sent, so that we know to handle them differently on return
    int Mc; // current number of partners. note that this is not the size of the partners set - ex. when we first join, this will be M, whilst partners.size() is 0.
            // you could also think of this as the "potential" number of partners, if everything resolves nicely excluding panic messages

    // timers
    cMessage* panic_timeout_timer; // the ttl on our panic has passed; send a new panic
    cMessage* panic_split_timeout_timer; // sama panicsplit
    cMessage* switch_timer; // switch to a new random mcache node

    // utility functions
    void count(int increment);
    void count_without_checking(int increment);
    void update_display_string();
    void update_and_check();
    TransportAddress get_random_in(std::set<TransportAddress> set);
    TransportAddress get_random_partner();
    TransportAddress get_random_partner_matching_predicate(std::function<bool(std::pair<TransportAddress, PartnerlinkEntry>)> const& lambda);
    std::map<TransportAddress, PartnerlinkEntry> get_partners();
    std::set<TransportAddress> get_partner_tads();
    double get_partner_percent_out_of_m();
    int get_starting_index();
    std::vector<TransportAddress> get_partner_k();
    std::map<TransportAddress, std::vector<int>> get_partner_latest_blocks();
    std::map<TransportAddress, TransportAddress> get_associations();
    void insert_partner_to_partners(TransportAddress partner);
    void remove_partner_from_partners(TransportAddress partner);
    bool is_timed_out(simtime_t origin_time, simtime_t timeout);

    // lifecycle
    void init(Node* p, int m, int mc, double pts, double pants, double pansts, double sis, int ssc, int tp_in, bool ds);

    // failure timers and buffermap timeout
    void set_failure_timer(TransportAddress partner);
    void remove_failure_timer(TransportAddress partner);
    void reset_failure_timer(TransportAddress partner);
    void read_failure_timer_and_fail_connection(Failure* failure);
    void recover_from_leaving_partner(TransportAddress partner);

    // panic tracking
    PanicStatus get_panic_status();
    void check_panic_status();
    void setup_panic();
    void setup_panic_split();
    void timeout_panic();
    void timeout_panic_split();

    // switching nodes from mcache
    void start_switch_from_mcache(TransportAddress switch_to);
    void reset_switch_timer();
    void finalize_mcache_switch(int uuid);
    void fail_mcache_switch(int uuid);


    // LINK_ORIGIN_NODES // UDP
    // construct the initial link between our two friendly origin nodes
    // that will be used to split between for newly joining nodes
    // in the real world we could secure this by validating the incoming nodeid
    // or through some kind of encryption/key message system.
    void send_link_origin_nodes_message(TransportAddress origin);
    void receive_link_origin_nodes_message(LinkOriginNodes* link_origin_nodes);

    // GET_CANDIDATE_PARTNERS // TCP
    // get list of possible starting partners from the deputy
    // timeout is handled by getting a new deputy in the MembershipManager
    void send_get_candidate_partners_message(TransportAddress tad);
    // TODO: remove the bandwidth from this when we can replace PartnershipManager
    void receive_get_candidate_partners_message_and_respond(GetCandidatePartnersCall* get_candidate_partners_call, std::map<TransportAddress, double> from_mCache);
    void receive_get_candidate_partners_response(GetCandidatePartnersResponse* get_candidate_partners_response);

    // SPLIT // TCP
    // request a node to split a relationship with a partner, and put this node in the middle
    void send_split_message(TransportAddress tad, bool is_mcache_switch = false);
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

    // LEAVE // UDP
    // tell a partner that we are leaving the network, so they can immediately switch to their associate
    void leave_overlay();
    void send_leave_message(TransportAddress tad);
    void receive_leave_message(Leave* leave);

    // PANIC // UDP
    // gossip a message looking for another panicking node we do not know, recovering one link to our node if found
    void panic_recover(TransportAddress panicking);
    TransportAddress get_best_next_hop_matching_panic_status(bool panic_status, TransportAddress panicking, TransportAddress last_hop);
    void send_panic_message(TransportAddress tad, TransportAddress panicking, simtime_t send_time = simTime());
    bool can_recover_panic(TransportAddress panicking);
    void receive_panic_message(PanicMsg* panic);

    // PANIC_SPLIT, PANIC_SPLIT_FOUND // UDP
    // gossip a message looking for two nodes that we do not know, but know each other, to split between, recovering two links to our node if found
    void panic_split_recover(TransportAddress panicking, TransportAddress last_hop);
    void send_panic_split_message(TransportAddress tad, TransportAddress panicking, simtime_t send_time = simTime(), LastHopOpinion last_hop_opinion = CANT_HELP);
    bool can_recover_panic_split(TransportAddress panicking, TransportAddress last_hop);
    void receive_panic_split_message(PanicSplitMsg* panic_split);
    void receive_panic_split_found_message(PanicSplitFound* panic_split_found);

    // RECOVER // UDP
    // tell a panicking partner we are willing to take up one of its missing partnerships
    void send_recover_message(TransportAddress tad);
    void receive_recover_message(Recover* recover); // make sure in here that if M == Mc, we ignore the message

    // BUFFER_MAP // UDP
    // receiving and caching buffermap-adjacent stats for our partners
    void receive_buffer_map_message(BufferMapMsg* buffer_map);

    PartnerlinkManager();
    virtual ~PartnerlinkManager();
};

#endif /* OVERLAY_COOLSTREAMING_PARTNERLINKMANAGER_H_ */
