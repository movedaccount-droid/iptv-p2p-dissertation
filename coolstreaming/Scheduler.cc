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
#include <algorithm>
#include <map>

// utility
#define setOrReplace(timer, name, offset) if (timer != NULL && timer->isScheduled()) { \
    parent->cancelEvent(timer); \
} else if (!timer) { \
    timer = new cMessage(name); \
} \
parent->scheduleAt(simTime() + offset, timer)

// lifecycle
void Scheduler::init(Node* p, int bsb, int bmei, int bl_s, int bsz) {
    parent = p;
    block_size_bits = bsb;
    bm_exchange_interval = bmei;
    block_length_s = bl_s;
    buffer_size = bsz;
    setOrReplace(exchange_timer, "exchange_timer", bm_exchange_interval);
}

void Scheduler::exchange(std::set<TransportAddress> partners, std::unordered_set<int> bm) {
    send_buffer_map_message_to_all_partners(partners, bm);
    setOrReplace(exchange_timer, "exchange_timer", bm_exchange_interval);
}

void Scheduler::request_buffer_map_blocks(std::unordered_set<int> expected_set, std::map<TransportAddress, PartnerEntry> partners, int playout_index) {
    // scheduling algorithm, fig 3.
    std::map<TransportAddress, std::unordered_map<int, int>> T; // maps block i to remaining transmission time
    std::map<TransportAddress, std::unordered_set<int>> supplier; // supplier of each block, though we switch this to a mapping of buffermaps to each partner for easy sending
    std::map<int, std::unordered_set<int>> dup_set; // set of blocks with more than one supplier, mapped to each supplier count

    // we modify this to make it bearable. fill T with base deadlines
    // and supplier with empty maps now instead of mid-process
    std::unordered_map<int, int> base_remaining_times;
    std::unordered_set<int> base_supplier;
    for (int segment : expected_set) {
        // this is approximate, but by all means should be good enough
        base_remaining_times.insert({segment, (playout_index - segment + 1) * block_length_s});
    }
    for (auto partner : partners) {
        T.insert({partner.first, base_remaining_times});
        supplier.insert({partner.first, base_supplier});
    }

    // now proceed as normal
    for (int segment_i : expected_set) {
        int n = 0;
        for (auto j : partners) {
            if (j.second.buffer_map.find(segment_i) != j.second.buffer_map.end()) n++;
        }
        if (n == 1) {
            for (auto k : partners) {
                // find actual k in map
                if (k.second.buffer_map.find(segment_i) != k.second.buffer_map.end()) {
                    supplier[k.first].insert(segment_i);
                    for (int j : expected_set) {
                        // i am almost certain this is i not k. k is a partner. that does not make sense
                        if (j > segment_i) {
                            T.at(k.first)[j] -= block_size_bits / partners.at(k.first).bandwidth;
                        }
                    }
                }
            }
        } else {
            dup_set[n].insert(segment_i);
            // whatever that null sattement is. we're not touching it
        }
    }
    // segments with dup.first potential suppliers
    for (auto dup : dup_set) {
        for (int segment_i : dup.second) {
            // get the highest bandwidth node [band(r) > band(r')]
            // amongst those we still have time to download from [t[r, i] > seg_size/band[r], t[r', i] > seg_size/band[r']]
            std::map<TransportAddress, PartnerEntry> k_candidates;
            for (auto partner : partners) {
                // this somehow isn't part of this algorithm but we still do it because we're not stupid
                if (partner.second.buffer_map.find(segment_i) != partner.second.buffer_map.end()
                && T.at(partner.first)[segment_i] > block_size_bits/partner.second.bandwidth) {
                    k_candidates.insert(partner);
                }
            }
            if (!k_candidates.empty()) {
                typedef typename decltype(k_candidates)::value_type& Comp;
                TransportAddress k = max_element(k_candidates.begin(), k_candidates.end(),
                                [](Comp l, Comp r) -> bool { return l.second.bandwidth < r.second.bandwidth;})->first;
                supplier[k].insert(segment_i);
                for (int j : expected_set) {
                    if (j > segment_i) {
                        T.at(k)[j] -= block_size_bits / partners.at(k).bandwidth;
                    }
                }
            }
        }
    }
    // send messages
    for (auto entry : supplier) {
        if (!entry.second.empty()) send_block_message(entry.first, entry.second);
    }
}

// BUFFER_MAP // UDP
// exchanging buffermap information to gain partial view of block availability
void Scheduler::send_buffer_map_message_to_all_partners(std::set<TransportAddress> partners, std::unordered_set<int> bm) {
    for (TransportAddress partner : partners) {
        BufferMap* buffer_map = new BufferMap();
        buffer_map->setFrom(parent->getThisNode());
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
    if (exchange_timer != NULL) parent->cancelAndDelete(exchange_timer);
}
