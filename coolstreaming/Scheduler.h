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
    int block_size; // block packet size in bytes
    int bm_exchange_interval; // time between each buffermap send
    int block_length; // block length in seconds
    int buffer_size; // max size of the buffermap

    cMessage* exchange_timer;

    // lifecycle
    void init(Node* p, int bs, int bmei, int bl, int bsz);
    void request_buffer_map_blocks(std::unordered_set<int> expected_set, std::vector<PartnerEntry> partners, int playout_index);

    // BUFFER_MAP // UDP
    // exchanging buffermap information to gain partial view of block availability
    void send_buffer_map_message_to_all_partners(std::vector<TransportAddress> partners, std::unordered_set<int> bm);
    // receive_buffer_map_message(BufferMap* buffer_map) => PartnershipManager.h

    // BLOCK // TCP
    // requesting blocks from partners to play
    void send_block_message(TransportAddress tad, std::unordered_set<int> bm);
    // receive_block_message(BlockCall* block_call) => Buffer.h
    void timeout_block_response(BlockCall* block_call);
    // receive_block_response(BlockResponse* block_response) => Buffer.h


    Scheduler() { exchange_timer = NULL; };
    virtual ~Scheduler();
};

#endif /* OVERLAY_COOLSTREAMING_SCHEDULER_H_ */
