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

#ifndef OVERLAY_MYOVERLAY_MEMBERSHIPMANAGER_H_
#define OVERLAY_MYOVERLAY_MEMBERSHIPMANAGER_H_

#include <chrono>
#include <unordered_map>
#include "mCacheEntry.h"
#include "common/TransportAddress.h"

class Node;
class MembershipManager {

private:
    Node* parent; // tad of parent
    std::vector<mCacheEntry> mCache; // membership cache
    std::vector<TransportAddress> inview; // inview listing
    std::unordered_map<int, int> uuidCounts; // message uuid counting
    int seq_num; // sequence number for next message
    int c; // SCAMP constant determining proportion of tolerated failures
    int scamp_resubscription_interval; // delay before resubscriptions, sub ttl
    int scamp_heartbeat_interval; // delay between heartbeats being sent
    int scamp_heartbeat_failure_interval; // delay between received heartbeats before resubbing

public:

    // timers, public for checking in parent
    cMessage *resubscription_timer;
    cMessage *unsubscription_timer;
    cMessage *send_heartbeat_timer;
    cMessage *no_heartbeat_timer;

    // lifecycle functions
    void init(Node* p, int cin, int scr, int sch, int schf);
    void join_overlay();
    void resubscribe();
    void unsubscribe();
    void send_heartbeats();
    void no_heartbeat();
    void leave_overlay();

    // utility functions
    mCacheEntry random_mcache_entry(TransportAddress exclude = TransportAddress());
    bool mcache_contains_tad(TransportAddress tad);
    void insert_mcache_entry(int seq_num, TransportAddress tad, int num_partner, simtime_t ttl);
    void remove_mcache_entry(TransportAddress tad);
    void remove_inview_entry(TransportAddress tad);

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
    void receive_membership_message(Membership* membership);

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
    { resubscription_timer = NULL; unsubscription_timer = NULL; send_heartbeat_timer = NULL; no_heartbeat_timer = NULL; };

    ~MembershipManager() {};
};

#endif /* OVERLAY_MYOVERLAY_MEMBERSHIPMANAGER_H_ */
