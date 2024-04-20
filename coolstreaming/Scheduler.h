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

#ifndef OVERLAY_COOLSTREAMING_SCHEDULER_H_
#define OVERLAY_COOLSTREAMING_SCHEDULER_H_

#import <unordered_set>
#include "common/TransportAddress.h"
#include "Coolstreaming_m.h"
#include "PartnerEntry.h"

// REMEMBER: AN EXCHANGE IS NOT A TRADE!!
// "regularly exchanges" means that node A regularly sends bm to B,
// and B regularly sends bm to A. these events are not necessarily
// related or tit-for-tat.

class Node;
class Scheduler {
public:
    Node* parent; // asdsdadgjfi0gi
    int block_size_bits; // block packet size in bits
    int bm_exchange_interval; // time between each buffermap send
    int block_length_s; // block length in seconds
    int buffer_size; // max size of the buffermap

    // we regularly exchange with all idle nodes to start download chains.
    // blocks are requested, and we set a timer to wait for how long
    // those blocks should take to receive, then exchange again.
    // nodes undergoing this chaining process are stored in active_nodes
    cMessage* exchange_timer;
    std::set<cMessage*> exchange_after_download_timers;
    std::set<TransportAddress> active_nodes;

    // lifecycle
    void init(Node* p, int bsb, int bmei, int bl_s, int bsz);
    void exchange_on_timer(std::set<TransportAddress> partners, std::unordered_set<int> bm);
    void request_buffer_map_blocks(std::unordered_set<int> expected_set, std::map<TransportAddress, PartnerEntry> partners, int playout_index);
    void exchange_after_download(ExchangeAfterDownload* exchange_after_download, std::unordered_set<int> buffer_map);

    // BUFFER_MAP // UDP
    // exchanging buffermap information to gain partial view of block availability
    void send_buffer_map_message(TransportAddress partner, std::unordered_set<int> bm);
    void send_buffer_map_message_to_all_idle_partners(std::set<TransportAddress> partners, std::unordered_set<int> bm);
    // receive_buffer_map_message(BufferMap* buffer_map) => PartnershipManager.h

    // BLOCK_REQUEST // UDP
    // requesting blocks from partners to play
    void send_block_request_message(TransportAddress tad, std::unordered_set<int> bm);
    // receive_block_request_message_and_respond(BlockRequest* block_request) => Buffer.h
    // receive_block_message(Block* block) => Buffer.h


    Scheduler() { exchange_timer = NULL; };
    virtual ~Scheduler();
};

#endif /* OVERLAY_COOLSTREAMING_SCHEDULER_H_ */
