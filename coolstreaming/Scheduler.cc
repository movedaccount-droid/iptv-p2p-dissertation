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

#include "../coolstreaming/Scheduler.h"
#include "Node.h"
#include "PartnerEntry.h"
#include <map>

// utility
#define setOrReplace(timer, name, offset) if (timer != NULL && timer->isScheduled()) { \
    parent->cancelEvent(timer); \
} else if (!timer) { \
    timer = new cMessage(name); \
} \
parent->scheduleAt(simTime() + offset, timer)

// lifecycle
void Scheduler::init(Node* p, int bs, int bmei, int bl, int bsz) {
    parent = p;
    block_size = bs;
    bm_exchange_interval = bmei;
    block_length = bl;
    buffer_size = bsz;
    setOrReplace(exchange_timer, "exchange_timer", bm_exchange_interval);
}

void Scheduler::request_buffer_map_blocks(std::unordered_set<int> expected_set, std::vector<PartnerEntry> partners, int playout_index) {
    // scheduling algorithm, fig 3.
    std::map<TransportAddress, std::unordered_map<int, int>> T;
    std::unordered_map<int, TransportAddress> supplier; // supplier of each block
    // we modify this to make it bearable. fill T with empty maps

//    // we modify this to make it bearable. fill T with empty maps
//    for (PartnerEntry partner : partners) {
//        std::unordered_map<int, int> empty;
//        T.push_back(std::make_pair(partner, empty));
//    }
//    // then fill all deadlines first
//    for (int segment : expected_set) {
//        // this is approximate, but by all means should be good enough
//        int remaining_time = (playout_index - segment + 1) * block_length;
//        for (auto pair : T) {
//            pair.second.insert(segment, remaining_time);
//        }
//    }
//    // now proceed as normal without dealing with deadline init
//    for (int segment : expected_set) {
//        // setting n: number of potential suppliers for segment i
//        int n = 0;
//        for (PartnerEntry partner : partners) {
//            if (partner.buffer_map.find(segment) != partner.buffer_map.end()) n++;
//        }
//        // segments with only one potential supplier
//        if (n == 1) {
//            // find k: single supplier for block
//            for (PartnerEntry partner : partners) {
//                if (partner.buffer_map.find(segment) != partner.buffer_map.end()) {
//                    supplier.insert(segment, k.tad);
//                    for (auto pair : )
//                }
//            }
//        }
//    }
}

// BUFFER_MAP // UDP
// exchanging buffermap information to gain partial view of block availability
void Scheduler::send_buffer_map_message_to_all_partners(std::vector<TransportAddress> partners, std::unordered_set<int> bm) {
    for (TransportAddress partner : partners) {
        BufferMap* buffer_map = new BufferMap();
        buffer_map->setBuffer_map(bm);
        parent->sendMessageToUDP(partner, buffer_map);
    }
}

// BLOCK // TCP
// requesting blocks from partners to play
void Scheduler::send_block_message(TransportAddress tad, std::unordered_set<int> bm) {
    BlockCall* block_call = new BlockCall();
    block_call->setBlocks(bm);
    parent->send_rpc(tad, block_call);
}

void Scheduler::timeout_block_response(BlockCall* block_call) {
    // worrying sign... but we ignore for now
}

Scheduler::~Scheduler() {
    parent->cancelAndDelete(exchange_timer);
}
