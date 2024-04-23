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

#ifndef OVERLAY_COOLSTREAMING_MEMBERSHIPMANAGER_H_
#define OVERLAY_COOLSTREAMING_MEMBERSHIPMANAGER_H_

#include <chrono>
#include <map>
#include <set>
#include <unordered_map>

#include "../coolstreaming/mCacheEntry.h"
#include "common/TransportAddress.h"

class Node;
class MembershipManager {

private:

    // variables
    Node* parent; // parent
    std::map<TransportAddress, mCacheEntry> mCache; // membership cache
    std::set<TransportAddress> inview; // inview listing
    std::unordered_map<int, int> uuidCounts; // message uuid counting
    int seq_num; // sequence number for next message

    // params
    TransportAddress origin_tad; // tad to contact to reach the origin
    double bandwidth; // bandwidth for this node
    int c; // SCAMP constant determining proportion of tolerated failures
    int scamp_resubscription_interval; // delay before resubscriptions, sub ttl
    int scamp_heartbeat_interval; // delay between heartbeats being sent
    int scamp_heartbeat_failure_interval; // delay between received heartbeats before resubbing
    int M; // target number of partners, needed to produce candidate_partners

public:

    // variables
    bool needs_deputy; // if we would like to be informed of deputies from any next get_deputies response

    // timers, public for checking in parent
    cMessage *resubscription_timer;
    cMessage *send_heartbeat_timer;
    cMessage *no_heartbeat_timer;

    // lifecycle functions
    void init(Node* p, TransportAddress ot, double b, int cin, int scr, int sch, int schf, int m);
    void join_overlay();
    void contact_deputy_and_enter_network(TransportAddress deputy);
    void resubscribe();
    void unsubscribe();
    void gossip_and_unsubscribe_failed_partner(TransportAddress failing);
    void send_heartbeats();
    void no_heartbeat();
    void leave_overlay();

    // utility functions
    std::pair<const TransportAddress, mCacheEntry> random_mcache_entry(TransportAddress exclude = TransportAddress());
    std::pair<const TransportAddress, mCacheEntry> random_mcache_entry(std::set<TransportAddress> exclude);
    void receive_get_candidate_partners_message_and_respond(GetCandidatePartnersCall* get_candidate_partners_call);
    void insert_mcache_entry(TransportAddress tad, int seq_num, int num_partner, simtime_t ttl, double bandwidth);
    void remove_mcache_entry(TransportAddress tad);

    // GET DEPUTY MESSAGES // TCP
    // gets deputy from origin node
    void send_get_deputy_message(TransportAddress tad);
    void receive_get_deputy_message_and_respond(GetDeputyCall* get_deputy_call, int block_index);
    void timeout_get_deputy_response(GetDeputyCall* get_deputy_call);
    void receive_get_deputy_response(GetDeputyResponse* get_deputy_response);

    // MEMBERSHIP MESSAGES // UDP
    // advertises existence of node to recipients
    // recipients may acknowledge and absorb message or pass it on
    void generate_membership_message(TransportAddress dest,
            int seq_num, TransportAddress tad, int num_partner,
            SimTime ttl, bool forwarded, bool entry = false, int uuid = rand());
    void send_entry_membership_message(TransportAddress tad);
    void send_membership_message(TransportAddress tad);
    void send_forced_membership_message(TransportAddress tad);
    void forward_membership_message(Membership* membership, TransportAddress tad);
    void absorb_membership_message(Membership* membership); // adds to mcache and sends inview
    bool receive_membership_message(Membership* membership);

    // INVIEW MESSAGES // TCP
    // informs node of membership acceptance and requests initiation to
    // inview list. if not received, the accepting node silently drops the acceptance
    void generate_inview_message(TransportAddress tad);
    void receive_inview_message_and_respond(InviewCall* inview_call);
    void timeout_inview_ack(InviewCall* inview_call);
    void receive_inview_ack();

    // UNSUBSCRIBE MESSAGES // UDP
    // informs nodes that they should swap their views. the paper is not
    // 100% clear on implementation [do we also update inviews?] but we
    // make a best effort
    void send_unsubscribe_message(TransportAddress tad, bool inview, TransportAddress replacement = TransportAddress());
    void receive_unsubscribe_message(Unsubscription* unsubscription);

    // GOSSIPED UNSUBSCRIBE MESSAGES // UDP
    // . okay. . Sent on Behalf of Failing Nodes when there has been no BM or Packet Transfer ???? in the . partner manager?? and no the fucking.  the fucking mcache???/
    // and Gossiped Similarly to SCAMP ?????????? What the fuck are you talking about
    void send_gossiped_unsubscribe_message(TransportAddress tad, TransportAddress failing);
    void receive_gossiped_unsubscribe_message(GossipedUnsubscription* gossiped_unsubscription);

    // HEARTBEAT MESSAGES // UDP
    // sent to nodes to inform that their neighbours are still alive.
    // if no heartbeat is received in some time, a node will resubscribe
    void send_heartbeat_message(TransportAddress tad);
    void receive_heartbeat_message(Heartbeat* heartbeat);

    MembershipManager():
        parent(),
        mCache(),
        seq_num(0),
        c()
    { resubscription_timer = NULL; send_heartbeat_timer = NULL; no_heartbeat_timer = NULL; };

    ~MembershipManager() {};
};

#endif /* OVERLAY_COOLSTREAMING_MEMBERSHIPMANAGER_H_ */
