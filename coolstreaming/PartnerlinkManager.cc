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

void PartnerlinkManager::count(int increment) {
    count_without_checking(increment);
    // int temp = Mc; // breakpoint here to capture all Mc changes and their call stack
    check_panic_status();
}

void PartnerlinkManager::count_without_checking(int increment) {
    Mc += increment;
    update_display_string();
}

void PartnerlinkManager::update_display_string() {
    if (display_string) {
        display_name = std::string("Mc: ")
            .append(std::to_string(Mc))
            .append(", P: ")
            .append(std::to_string(partners.size()))
            .append(", IP: ")
            .append(parent->getThisNode().getIp().str())
            .append(", Part%: ")
            .append(std::to_string(get_partner_percent_out_of_m()));
        bool panicking = (get_panic_status() != Nominal);
        bool perfect = partners.size() == Mc && Mc == M;
        if (panicking) display_name = std::string("[PANIC] ").append(display_name);
        cDisplayString& ds = parent->getParentModule()->getParentModule()->getDisplayString();
        ds.setTagArg("t", 0, display_name.c_str());
        ds.setTagArg("t", 2, perfect ? "cornflowerblue" : panicking ? "red" : "blue");
    }
}

void PartnerlinkManager::update_and_check() {
    check_panic_status();
    update_display_string();
}

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

TransportAddress PartnerlinkManager::get_random_partner_matching_predicate(std::function<bool(std::pair<TransportAddress, PartnerlinkEntry>)> const& predicate) {
    std::set<TransportAddress> matching_partners;
    for (auto entry : partners) {
        if (predicate(entry)) {
            matching_partners.insert(entry.first);
        }
    }
    return get_random_in(matching_partners);
}

std::map<TransportAddress, PartnerlinkEntry> PartnerlinkManager::get_partners() {
    return partners;
}

std::set<TransportAddress> PartnerlinkManager::get_partner_tads() {
    std::set<TransportAddress> partner_tads;
    for (auto partner : partners) {
        partner_tads.insert(partner.first);
    }
    return partner_tads;
}

double PartnerlinkManager::get_partner_percent_out_of_m() {
    // partners are Fully, Really initialized after we have received their buffer map
    int with_buffer_map = 0;
    for (auto partner : partners) {
        if (partner.second.buffer_map_received())
            with_buffer_map++;
    }
    return with_buffer_map / (double)M;
}

int PartnerlinkManager::get_starting_index() {
    int starting_index = 0;
    for (auto partner : get_partner_latest_blocks()) {
        int max_total_block = *max_element(partner.second.begin(), partner.second.end());
        if (max_total_block > starting_index) starting_index = max_total_block;
    }
    return starting_index - tp;
}

// TODO: this is doumb as fuck and needs removing at some point
std::vector<TransportAddress> PartnerlinkManager::get_partner_k() {
    std::vector<TransportAddress> partner_k;
    for (auto partner : partners) {
        partner_k.push_back(partner.first);
    }
    return partner_k;
}

std::map<TransportAddress, std::vector<int>> PartnerlinkManager::get_partner_latest_blocks() {
    std::map<TransportAddress, std::vector<int>> latest_blocks;
    for (auto partner : partners) {
        latest_blocks.insert({partner.first, partner.second.latest_blocks});
    }
    return latest_blocks;
}

std::map<TransportAddress, TransportAddress> PartnerlinkManager::get_associations() {
    // TODO: this is a basic implementation and will later be replaced
    std::map<TransportAddress, TransportAddress> associations;
    auto partner = partners.begin();
    while (partner != partners.end()) {
        TransportAddress first = partner->first;
        partner++;
        if (partner == partners.end()) {
            associations.insert({first, TransportAddress()});
            break;
        } else {
            associations.insert({{first, partner->first}, {partner->first, first}});
            partner++;
        }
    }
//    std::cout << "assocs running..." << std::endl;
//    for (auto assoc : associations) {
//        std::cout << parent->getThisNode().getIp().str() << ": assoc " << assoc.first.getIp().toIPv4().getInt() << " (" << assoc.first.getIp().str() << ") to " <<
//                assoc.second.getIp().toIPv4().getInt() << " (" << assoc.second.getIp().str() << ")" << std::endl;
//    }
    return associations;
}

// we adjust Mc in these following functions.
// you should manually track whatever your action SHOULD do to Mc,
// and these functions will automatically adjust if there are duplicate partners etc.

// i.e. failing a connection to timeout should reduce Mc by 1,
// so we call remove_partner_from_partners and Mc-- and check_panic_status in sequence.
// if we somehow timeout a partner that we don't know, however,
// the function will correct our value for us.

void PartnerlinkManager::insert_partner_to_partners(TransportAddress partner) {
    auto partner_entry = partners.find(partner);
    if (partner_entry != partners.end()) {
        count_without_checking(-1); // we added a connection but already knew it
        parent->getParentModule()->getParentModule()->bubble(std::string("[!] attempted to insert partner ")
            .append(partner.getIp().str())
            .append(" but we already know it!").c_str());
    } else {
        partners.insert({partner, PartnerlinkEntry(substream_count, false)});
        parent->set_arrow(partner, "PARTNER", true);
        parent->getParentModule()->getParentModule()->bubble(std::string("partnered with node ")
            .append(partner.getIp().str())
            .append("...").c_str());
        set_failure_timer(partner);
    }
}

void PartnerlinkManager::remove_partner_from_partners(TransportAddress partner) {
    auto partner_entry = partners.find(partner);
    if (partner_entry == partners.end()) {
        count_without_checking(1); // we removed a connection but didn't know it
        parent->getParentModule()->getParentModule()->bubble(std::string("[!] attempted to remove partner ")
            .append(partner.getIp().str())
            .append(" but we don't know it!").c_str());
    } else {
        partners.erase(partner);
        parent->set_arrow(partner, "PARTNER", false);
        parent->getParentModule()->getParentModule()->bubble(std::string("removed partner node ")
            .append(partner.getIp().str())
            .append("...").c_str());
        remove_failure_timer(partner);
    }
}

bool PartnerlinkManager::is_timed_out(simtime_t origin_time, simtime_t timeout) {
    return simTime() - origin_time > timeout;
}

// lifecycle
void PartnerlinkManager::init(Node* p, int m, int mc, double pts, double pants, double pansts, double sis, int ssc, int tp_in, bool ds) {
    parent = p;
    M = m;
    Mc = mc;
    partnership_timeout = SimTime(pts, SIMTIME_S);
    panic_timeout = SimTime(pants, SIMTIME_S);
    panic_split_timeout = SimTime(pansts, SIMTIME_S);
    switch_interval = SimTime(sis, SIMTIME_S);
    substream_count = ssc;
    tp = tp_in;
    display_string = ds;
    needs_deputy = !parent->origin;
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
    parent->getParentModule()->getParentModule()->bubble(std::string("timed out partner ").append(failure->getFailed().getIp().str()).append("...").c_str());
    recover_from_leaving_partner(failure->getFailed());
}

void PartnerlinkManager::recover_from_leaving_partner(TransportAddress partner) {

    // this is where the association system comes into play. if we've been given an associate,
    // we immediately swap to them and don't adjust our Mc. if we never got one, were associated
    // with the unspecified address, or that new connection doesn't resolve, THEN we panic.
    // in most cases in substantial networks this means nodes do not have to gossip any messages
    // to recover from a node leaving, cleanly or otherwise.

    TransportAddress associate = partners.at(partner).associate;
    if (associate.isUnspecified()) {
        remove_partner_from_partners(partner);
        count(-1);
    } else {
        remove_partner_from_partners(partner);
        insert_partner_to_partners(associate);
        update_and_check();
    }
}

// panic management
PanicStatus PartnerlinkManager::get_panic_status() {
    if (Mc == M) {
        return Nominal;
    } else if (Mc == 0) {
        return TotalFailure;
    } else if (Mc == M - 1) {
        return Panic;
    } else if (Mc == M - 2) {
        return PanicSplit;
    } else {
        return PanicBoth;
    }
}

void PartnerlinkManager::check_panic_status() {
    if (!(Mc <= M && Mc >= 0)) {
        std::cout << parent->getThisNode().getIp().str() << std::endl;
        std::cout << "Mc was " << Mc << std::endl;
        assert(false);
    }
    if (partners.size() > Mc) {
        std::cout << parent->getThisNode().getIp().str() << std::endl;
        std::cout << "Mc was " << Mc << std::endl;
        std::cout << "partners was " << partners.size() << std::endl;
        assert(false);
    }
    switch (get_panic_status()) {
    case Nominal:
        // awesome. cancel everything because we don't care anymore
        if (panic_timeout_timer != NULL) {
            parent->cancelAndDelete(panic_timeout_timer);
            panic_timeout_timer = NULL;
        }
        if (panic_split_timeout_timer != NULL) {
            parent->cancelAndDelete(panic_split_timeout_timer);
            panic_split_timeout_timer = NULL;
        }
        break;
    case Panic:

        // assume that we entered this from PanicSplit. there might still be a PanicSplit in the
        // network, and if we hear back from it, accepting one of the links would cause net-zero
        // damage to the network, as opposed to ignoring it in favor of our Panic which would add
        // one panicking node. so we wait until PanicSplit times out to continue

        if (panic_timeout_timer == NULL && panic_split_timeout_timer == NULL) setup_panic();
        break;
    case PanicSplit:
        // same logic
        if (panic_timeout_timer == NULL && panic_split_timeout_timer == NULL) setup_panic_split();
        break;
    case PanicBoth:
        // here both should be out anyway, so who cares
        if (panic_timeout_timer == NULL) setup_panic();
        if (panic_split_timeout_timer == NULL) setup_panic_split();
        break;
    case TotalFailure:
        // that's not good. reset partner collection from scratch, from within the membership manager
        cMessage* total_partner_failure = new TotalPartnerFailure();
        parent->scheduleAt(simTime() + 0.001, total_partner_failure);
        break;
    }
}

void PartnerlinkManager::setup_panic() {

    // checking partners.size here seems silly, but remember that nodes
    // receiving less than M / 2 partners at entry will immediately start
    // panicking; Mc might be M - 2, but partners will still be 0!

    if (partners.size() > 0) {
        send_panic_message(get_random_partner(), parent->getThisNode());
        setOrReplace(panic_timeout_timer, "panic message timed out", panic_timeout);
    }
}

void PartnerlinkManager::setup_panic_split() {
    if (partners.size() > 0) {
        send_panic_split_message(get_random_partner(), parent->getThisNode());
        setOrReplace(panic_split_timeout_timer, "panic message timed out", panic_split_timeout);
    }
}

// TODO: actually hook these into the Node functions
void PartnerlinkManager::timeout_panic() {
    parent->cancelAndDelete(panic_timeout_timer);
    panic_timeout_timer = NULL;
    check_panic_status();
}

void PartnerlinkManager::timeout_panic_split() {
    parent->cancelAndDelete(panic_split_timeout_timer);
    panic_split_timeout_timer = NULL;
    check_panic_status();
}

// switching nodes from mcache
void PartnerlinkManager::start_switch_from_mcache(TransportAddress switch_to) {
    send_split_message(switch_to, true);
    setOrReplace(switch_timer, "switch_timer", switch_interval);
}

void PartnerlinkManager::reset_switch_timer() {
    // called when we have no non-partner mcache entries to choose from
    setOrReplace(switch_timer, "switch_timer", switch_interval);
}

void PartnerlinkManager::finalize_mcache_switch(int uuid) {
    active_switch_messages.erase(uuid);
    // request two random associated nodes to link, only picking
    // nodes that will panic if we have to
    std::map<TransportAddress, TransportAddress> associations = get_associations();
    std::set<TransportAddress> has_associate;
    for (auto association : associations) {
        if (!association.second.isUnspecified()) {
            has_associate.insert(association.first);
        }
    }
    try {
        if (has_associate.size() > 0) {
            TransportAddress replaced = get_random_in(has_associate);
            send_leave_message(associations[replaced]);
            remove_partner_from_partners(associations[replaced]);
            send_leave_message(replaced);
            remove_partner_from_partners(replaced);
        } else {
            TransportAddress replaced = get_random_partner();
            send_leave_message(replaced);
            remove_partner_from_partners(replaced);
        }
    } catch (const char* c) {} // i don't think this can happen. but i'd rather not find out!
}

void PartnerlinkManager::fail_mcache_switch(int uuid) {
    active_switch_messages.erase(uuid);
}

// LINK_ORIGIN_NODES // UDP
// construct the initial link between our two friendly origin nodes
// that will be used to split between for newly joining nodes
// in the real world we could secure this by validating the incoming nodeid
// or through some kind of encryption/key message system.
void PartnerlinkManager::send_link_origin_nodes_message(TransportAddress origin) {
    LinkOriginNodes* link_origin_nodes = new LinkOriginNodes();
    link_origin_nodes->setOrigin(parent->getThisNode());
    parent->sendMessageToUDP(origin, link_origin_nodes, SimTime(100, SIMTIME_MS));
}

void PartnerlinkManager::receive_link_origin_nodes_message(LinkOriginNodes* link_origin_nodes) {
    insert_partner_to_partners(link_origin_nodes->getOrigin());
    count(1);
}

// GET CANDIDATE PARTNERS MESSAGES // TCP
// get list of possible starting partners from the deputy
void PartnerlinkManager::send_get_candidate_partners_message(TransportAddress tad) {
    GetCandidatePartnersCall* get_candidate_partners_call = new GetCandidatePartnersCall();
    get_candidate_partners_call->setFrom(parent->getThisNode());
    parent->send_rpc(tad, get_candidate_partners_call);
    needs_deputy = false;
}

// TODO: remove use of bandwidth ??? in here
void PartnerlinkManager::receive_get_candidate_partners_response(GetCandidatePartnersResponse* get_candidate_partners_response) {
    // we might not receive M partners, so we need to adjust our prospective partner count accordingly
    Mc = get_candidate_partners_response->getCandidates().size() * 2;
    check_panic_status();
    for (auto candidate : get_candidate_partners_response->getCandidates()) {
        send_split_message(candidate.first);
    }
    // TODO: we need to enable this eventually
    setOrReplace(switch_timer, "switch_timer", switch_interval);
    parent->getParentModule()->getParentModule()->bubble(std::string("received ")
        .append(std::to_string(get_candidate_partners_response->getCandidates().size()))
        .append(" candidates...").c_str());
}

// SPLIT // TCP
// request a node to split a relationship with a partner, and put this node in the middle
void PartnerlinkManager::send_split_message(TransportAddress tad, bool is_mcache_switch) {
    int uuid = rand();
    if (is_mcache_switch) active_switch_messages.insert(uuid); // see switch_from_mcache()
    SplitCall* split_call = new SplitCall();
    split_call->setInto(parent->getThisNode());
    split_call->setUuid(uuid);
    parent->send_rpc(tad, split_call);
}

void PartnerlinkManager::receive_split_message_and_try_split_with_partner(SplitCall* split_call) {

    // partners could be zero here, or in almost any case for new nodes
    // in the very unfortunate event they are accepted by a node who sends
    // a message and then immediately churns. even if you don't think you
    // need to handle the zero-partners case - you probably do!

    if (parent->leaving
            || partners.size() == 0
            || partners.find(split_call->getInto()) != partners.end()) {
        send_split_failure_response(split_call);
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
    split_response->setUuid(split_call->getUuid());
    parent->send_rpc_response(split_call, split_response);
}

void PartnerlinkManager::receive_split_response(SplitResponse* split_response) {
    bool was_scheduled_switch = active_switch_messages.find(split_response->getUuid()) != active_switch_messages.end();
    if (split_response->getResult() == SUCCESS) {
        if (parent->leaving) {
            // send Leave messages to force the other nodes to panic faster
            send_leave_message(split_response->getFirst_node());
            send_leave_message(split_response->getSecond_node());
        } else {
            // if we already know one of these, we start Panicking
            insert_partner_to_partners(split_response->getFirst_node());
            insert_partner_to_partners(split_response->getSecond_node());
            if (was_scheduled_switch) {
                finalize_mcache_switch(split_response->getUuid());
            }
            update_and_check();
        }
    } else {
        if (was_scheduled_switch) {
            fail_mcache_switch(split_response->getUuid());
        } else {
            count(-2); // causing the node to start sending PanicSplits
        }
    }
}

void PartnerlinkManager::timeout_split_response(SplitCall* split_call) {
    if (!active_switch_messages.erase(split_call->getUuid())) {
        count(-2); // causing the node to start sending PanicSplits
    };
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
    if (parent->leaving
            || partners.find(try_split_call->getInto()) != partners.end()
            || partners.find(try_split_call->getFrom()) == partners.end()) {
        try_split_response->setResult(FAILED);
    } else {
        remove_partner_from_partners(try_split_call->getFrom());
        insert_partner_to_partners(try_split_call->getInto());
        update_and_check();
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
    // the same logic applies to responding whilst we are leaving

    SplitCall* split_call = currently_splitting[try_split_response->getUuid()];
    if (try_split_response->getResult() == FAILED
            || partners.find(try_split_response->getFrom()) == partners.end()) {
        send_split_failure_response(split_call);
    } else {
        remove_partner_from_partners(try_split_response->getFrom());
        insert_partner_to_partners(try_split_response->getInto());
        update_and_check();
        SplitResponse* split_response = new SplitResponse();
        split_response->setResult(SUCCESS);
        split_response->setUuid(try_split_response->getUuid());
        split_response->setFirst_node(parent->getThisNode());
        split_response->setSecond_node(try_split_response->getFrom());
        parent->send_rpc_response(split_call, split_response);
    }
}
void PartnerlinkManager::timeout_try_split_response(TrySplitCall* try_split_call) {
    SplitCall* split_call = currently_splitting[try_split_call->getUuid()];
    send_split_failure_response(split_call);
}

// LEAVE // UDP
// tell a partner that we are leaving the network, so they can immediately switch to their associate
void PartnerlinkManager::leave_overlay() {
    for (auto partner : partners) {
        send_leave_message(partner.first);
    }
}

void PartnerlinkManager::send_leave_message(TransportAddress tad) {
    Leave* leave = new Leave();
    leave->setFrom(parent->getThisNode());
    parent->sendMessageToUDP(tad, leave);
}

void PartnerlinkManager::receive_leave_message(Leave* leave) {
    parent->getParentModule()->getParentModule()->bubble(std::string("partner ").append(leave->getFrom().getIp().str()).append(" leaving...").c_str());
    recover_from_leaving_partner(leave->getFrom());
}

// PANIC // UDP
// gossip a message looking for another panicking node we do not know, recovering one link to our node if found
// TODO: we need to oincorporate panicking in to the buffer map, we waren't riht now and just model everything as if iit is not panicking
TransportAddress PartnerlinkManager::get_best_next_hop_matching_panic_status(bool panic_status, TransportAddress panicking, TransportAddress last_hop) {
    try {
        auto partner_with_panic_status = [=](std::pair<const TransportAddress, PartnerlinkEntry> pair) {
            return pair.second.panicking == panic_status && pair.first != last_hop && pair.first != panicking;
        };
        return get_random_partner_matching_predicate(partner_with_panic_status);
    } catch (const char* c) {
        try {
            auto not_return_path = [=](std::pair<const TransportAddress, PartnerlinkEntry> pair) {
                TransportAddress temp = last_hop;
                if (last_hop.isUnspecified()) {
                    std::cout << "some" << std::endl;
                }
                return pair.first != last_hop && pair.first != panicking;
            };
            return get_random_partner_matching_predicate(not_return_path);
        } catch (const char* c) {
            // caller must catch exception from here themselves
            return get_random_partner();
        }
    }
}

void PartnerlinkManager::panic_recover(TransportAddress panicking) {
    insert_partner_to_partners(panicking);
    send_recover_message(panicking);
    count(1);
}

void PartnerlinkManager::send_panic_message(TransportAddress tad, TransportAddress panicking, simtime_t send_time) {
    PanicMsg* panic = new PanicMsg();
    panic->setPanicking(panicking);
    panic->setLast_hop(parent->getThisNode());
    panic->setSend_time(send_time);
    parent->sendMessageToUDP(tad, panic);
}

bool PartnerlinkManager::can_recover_panic(TransportAddress panicking) {
    // check that we are panicking and don't know the node
    return !parent->leaving
            && get_panic_status() != Nominal
            && panicking != parent->getThisNode()
            && partners.find(panicking) == partners.end();
}

void PartnerlinkManager::receive_panic_message(PanicMsg* panic) {
    if (is_timed_out(panic->getSend_time(), panic_timeout)) {
        return;
    }
    if (can_recover_panic(panic->getPanicking())) {
        panic_recover(panic->getPanicking());
    } else {
        try {
            // direct the message towards panicking nodes in our view, resolving the message M times faster [this is probably not true]
            TransportAddress random_partner = get_best_next_hop_matching_panic_status(true, panic->getPanicking(), panic->getLast_hop());
            send_panic_message(random_partner, panic->getPanicking(), panic->getSend_time());
        } catch (const char* c) {} // sucks but we can't do anything
    }
}

// PANIC_SPLIT // UDP
// gossip a message looking for two nodes that we do not know, but know each other, to split between, recovering two links to our node if found
void PartnerlinkManager::panic_split_recover(TransportAddress panicking, TransportAddress last_hop) {
    remove_partner_from_partners(last_hop);
    insert_partner_to_partners(panicking);
    send_recover_message(panicking);
    update_and_check();
}

void PartnerlinkManager::send_panic_split_message(TransportAddress tad, TransportAddress panicking, simtime_t send_time, LastHopOpinion last_hop_opinion) {
    PanicSplitMsg* panic_split_msg = new PanicSplitMsg();
    panic_split_msg->setPanicking(panicking);
    panic_split_msg->setLast_hop(parent->getThisNode());
    panic_split_msg->setLast_hop_opinion(last_hop_opinion);
    panic_split_msg->setSend_time(send_time);
    parent->sendMessageToUDP(tad, panic_split_msg);
}

bool PartnerlinkManager::can_recover_panic_split(TransportAddress panicking, TransportAddress last_hop) {
    // check that we don't know the node and are partnered with the last hop
    return !parent->leaving
            && panicking != parent->getThisNode()
            && partners.find(panicking) == partners.end()
            && partners.find(last_hop) != partners.end();
}

void PartnerlinkManager::receive_panic_split_message(PanicSplitMsg* panic_split) {
    if (is_timed_out(panic_split->getSend_time(), panic_split_timeout)) {
        return;
    }
    bool can_help = can_recover_panic_split(panic_split->getPanicking(), panic_split->getLast_hop());
    if (can_help && panic_split->getLast_hop_opinion() == CAN_HELP) {
        PanicSplitFound* panic_split_found = new PanicSplitFound();
        panic_split_found->setPanicking(panic_split->getPanicking());
        panic_split_found->setLast_hop(parent->getThisNode());
        parent->sendMessageToUDP(panic_split->getLast_hop(), panic_split_found);
        panic_split_recover(panic_split->getPanicking(), panic_split->getLast_hop());
    } else {
        try {
            // direct the message away from panicking nodes, for maximum visibility and to ensure our new partners are stable
            TransportAddress random_partner = get_best_next_hop_matching_panic_status(false, panic_split->getPanicking(), panic_split->getLast_hop());
            send_panic_split_message(random_partner, panic_split->getPanicking(), panic_split->getSend_time(), can_help ? CAN_HELP : CANT_HELP);
        } catch (const char* c) {} // nowhere to send...
    }
}

void PartnerlinkManager::receive_panic_split_found_message(PanicSplitFound* panic_split_found) {
    if (can_recover_panic_split(panic_split_found->getPanicking(), panic_split_found->getLast_hop())) {
        panic_split_recover(panic_split_found->getPanicking(), panic_split_found->getLast_hop());
    } else {
        // something very stupid has happened - the other side may or may not end up being successful.
        // we can in the meantime treat this like a normal Panic message
        if (can_recover_panic(panic_split_found->getPanicking())) {
            panic_recover(panic_split_found->getPanicking());
        }
    }
}

// RECOVER // UDP
// tell a panicking partner we are willing to take up one of its missing partnerships
void PartnerlinkManager::send_recover_message(TransportAddress tad) {
    Recover* recover = new Recover();
    recover->setHelper(parent->getThisNode());
    parent->sendMessageToUDP(tad, recover);
}

void PartnerlinkManager::receive_recover_message(Recover* recover) {
    // if we have already since recovered, we should ignore the message and let the node fail
    if (get_panic_status() != Nominal) {
        insert_partner_to_partners(recover->getHelper());
        count(1);
    }

}

// BUFFER_MAP // UDP
// receiving and caching buffermap-adjacent stats for our partners
void PartnerlinkManager::receive_buffer_map_message(BufferMapMsg* buffer_map) {
    auto partner = partners.find(buffer_map->getFrom());
    if (partner != partners.end()) {
        partner->second.latest_blocks = buffer_map->getBuffer_map().first;
        partner->second.associate = buffer_map->getAssociate();
        reset_failure_timer(buffer_map->getFrom());
    }
}

PartnerlinkManager::PartnerlinkManager() {
    panic_timeout_timer = NULL;
    panic_split_timeout_timer = NULL;
    switch_timer = NULL;
}

PartnerlinkManager::~PartnerlinkManager() {
    if (panic_timeout_timer != NULL) parent->cancelAndDelete(panic_timeout_timer);
    if (panic_split_timeout_timer != NULL) parent->cancelAndDelete(panic_split_timeout_timer);
    if (switch_timer != NULL) parent->cancelAndDelete(switch_timer);
    for (auto failure : fail_connection_timers) {
        parent->cancelAndDelete(failure.second);
    }
}

