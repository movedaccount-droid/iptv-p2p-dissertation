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
#include <deque>
#include "StreamManager.h"
#include "Node.h"

// utility
#define setOrReplace(timer, name, offset) if (timer != NULL && timer->isScheduled()) { \
    parent->cancelEvent(timer); \
} else if (!timer) { \
    timer = new cMessage(name); \
} \
parent->scheduleAt(simTime() + offset, timer)

// lifecycle
void StreamManager::init(Node* p, int sc, int bls, int bsb) {
    parent = p;
    substream_count = sc;
    block_length_s = bls;
    block_size_bits = bsb;
    playing = false;
    playout_index = 0;
    buffers = std::vector<std::deque<int>>(substream_count, std::deque<int>());
    subscribers = std::vector<std::map<TransportAddress, int>>(substream_count, std::map<TransportAddress, int>());
}

void StreamManager::start(int start_index) {
    playout_index = start_index;
    playing = true;
    playout();
}

void StreamManager::reselect_partners_and_exchange(std::map<TransportAddress, std::vector<int>> partner_latest_blocks, int max_block_in_partners) {
    for (auto substream : parents) {
        int j = substream.first;
        TransportAddress parent = substream.second;

        // check if parent is failing
        // inequality 1: limiting maximum fall-behind on single substream within node
        std::set<int> abs_hsia_hsjp;
        int hsjp = partner_latest_blocks[parent].second[j];
        for (int all_ss = 0; all_ss < substream_count; ++all_ss) {
            int hsia = buffers[i].size() == 0 ? 0 : buffers[i].back();
            abs_hsia_hsjp.insert(buffers[ss].back() - )
                    // abs() for aBSOLUTE
        }
    }
}

void StreamManager::playout() {
    setOrReplace(playout_timer, "playout_timer", block_length_s);
    if (buffers[substream(playout_index)].front() == playout_index) {
        buffers[substream(playout_index)].pop();
        // TODO: and measure stats
    } else {
        // TODO: missed playout... blahhhh atasts
    }
    playout_index++;
    if (playout_timer != NULL) parent->cancelAndDelete(playout_timer);
}

void StreamManager::end() {
    // TODO: commit stats
    playing = false;
}

// utility
std::vector<int> StreamManager::get_buffer_map() {
    std::vector<int> latest_blocks;
    for (int ss = 0; ss < substream_count; ++ss) {
        latest_blocks.push_back(buffers[ss].back());
    }
    return latest_blocks;
}

// BUFFER_MAP // UDP
// exchange buffer_maps with peers to update local view of blocks
// remember: exchange doesn't mean tit-for-tat!! the two nodes
// send each other the map in their own time, by their own timer
void StreamManager::send_buffer_map_message(TransportAddress partner, BufferMap buffer_map) {
    BufferMapMsg* buffer_map_msg = new BufferMapMsg();
    buffer_map_msg->setFrom(parent->getThisNode());
    buffer_map_msg->setBuffer_map(buffer_map);
    parent->sendMessageToUDP(partner, buffer_map_msg);
}

void StreamManager::receive_buffer_map_subscriptions(BufferMapMsg* buffer_map_msg) {
    auto incoming_subscriptions = buffer_map_msg.getBuffer_map().second;
    for (int ss = 0; ss < substream_count; ++ss) {
        auto entry = incoming_subscriptions.find(ss);
        if (entry != incoming_subscriptions.end()) {
            subscribers[ss].insert(buffer_map_msg.getFrom(), entry.second);
        }
    }
}

// BLOCK // UDP
// sending a block to a child partner, who then forwards it to their children
void StreamManager::send_block_message(TransportAddress child, int index, bool triggers_send) {
    Block* block = new Block();
    block->setIndex(index);
    block->setTriggers_send(triggers_send);
    block->setBitLength(block_size_bits);
    parent->sendMessageToUDP(child, block);
}

std::map<TransportAddress, int> StreamManager::receive_block_message(Block* block) {
    int index = block->getIndex();
    int substream_id = index % substream_count;
    auto substream = buffers[substream_id];
    bool is_next_block;

    // check if this is the next block in line
    if (substream.size() == 0) {
        // manually calculate the correct block
        int current_substream_id = playout_index % substream_count;
        int diff = substream_id - current_substream_id;
        if (diff < 0) diff += substream_count;
        is_next_block = index == playout_index + diff;
    } else {
        is_next_block = index - substream_count == substream.back();
    }

    // accept correct block
    if (is_next_block) {
        substream.push_back(index);
    }

    // either way push blocks to subscribers. if the block is still catching up, send two blocks
    // when we do this, that block would send four blocks, eight, sixteen etc. in turn
    // to avoid this we only allow the second block to trigger forwarding; the following node thus only sends two blocks
    if (block->getTriggers_send() && substream.size() > 0) {
        for (auto child_entry : subscribers[substream_id]) {
            std::vector<int> to_send;

            while (to_send.size() < 2 && std::find(substream.begin(), substream.end(), child_entry.second) != substream.end()) {
                to_send.push_back(child_entry.second);
                child_entry.second += substream_count;
            }

            for (auto it = to_send.begin(); it != to_send.end(); ++it) {
                send_block_message(child_entry.first, *it, it == to_send.end());
            }
        }
    }
}


StreamManager::~StreamManager() {
    if (exchange_timer != NULL) parent->cancelAndDelete(exchange_timer);
    if (playout_timer != NULL) parent->cancelAndDelete(playout_timer);
}
