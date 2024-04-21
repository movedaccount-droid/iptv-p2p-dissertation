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
#include <random>
#include "../coolstreaming/Node.h"
#include "StreamManager.h"

// utility
#define setOrReplace(timer, name, offset) if (timer != NULL && timer->isScheduled()) { \
    parent->cancelEvent(timer); \
} else if (!timer) { \
    timer = new cMessage(name); \
} \
parent->scheduleAt(simTime() + offset, timer)

// lifecycle
void StreamManager::init(Node* p, int sc, int bls, int bsb, int ts_in, int tp_in) {
    parent = p;
    substream_count = sc;
    block_length_s = bls;
    block_size_bits = bsb;
    playing = false;
    playout_index = 0;
    ts = ts_in;
    tp = tp_in;
    buffers = std::vector<std::deque<int>>(substream_count, std::deque<int>());
    substream_children = std::vector<std::map<TransportAddress, int>>(substream_count, std::map<TransportAddress, int>());
    substream_parents = std::vector<TransportAddress>(substream_count, TransportAddress());
}

void StreamManager::start(int start_index) {
    playout_index = start_index;
    playing = true;
    playout();
}

void StreamManager::reselect_partners_and_exchange(std::map<TransportAddress, std::vector<int>> partner_latest_blocks) {
    for (int ss = 0; ss < substream_count; ++ss) {
        TransportAddress parent = substream_parents[ss];
        if (parent.isUnspecified() || is_partner_failing(parent, ss, partner_latest_blocks)) {
            // ensure our selection is random
            std::vector<TransportAddress> random_candidate;
            for (auto candidate : partner_latest_blocks) {
                random_candidate.push_back(candidate.first);
            }
            std::random_device ran;
            std::mt19937 rng(ran());
            std::shuffle(random_candidate.begin(), random_candidate.end(), rng);

            for (TransportAddress candidate : random_candidate) {
                if (!is_partner_failing(candidate, ss, partner_latest_blocks)) {

                    break;
                }
            }
        }
    }
}

void StreamManager::playout() {
    setOrReplace(playout_timer, "playout_timer", block_length_s);
    if (buffers[playout_index % substream_count].front() == playout_index) {
        buffers[playout_index % substream_count].pop_front();
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
int StreamManager::get_next_needed_block(int substream) {
    if (buffers[substream].size() == 0) {
        // manually calculate the correct block
        int current_substream_id = playout_index % substream_count;
        int diff = substream - current_substream_id;
        if (diff < 0) diff += substream_count;
        return playout_index + diff;
    } else {
        return buffers[substream].back() + substream_count;
    }
}

int StreamManager::get_playout_index() {
    return playout_index;
}

BufferMap StreamManager::get_buffer_map(TransportAddress partner) {
    return std::make_pair(get_latest_blocks(), get_subscription_map(partner));
}

std::vector<int> StreamManager::get_latest_blocks() {
    std::vector<int> latest_blocks;
    for (int ss = 0; ss < substream_count; ++ss) {
        latest_blocks.push_back(buffers[ss].back());
    }
    return latest_blocks;
}

std::map<int, int> StreamManager::get_subscription_map(TransportAddress partner) {
    std::map<int, int> subscription_map;
    for (int ss = 0; ss < substream_count; ++ss) {
        if (substream_parents[ss] == partner) {
            subscription_map.insert({ss, get_next_needed_block(ss)});
        }
    }
    return subscription_map;
}

bool StreamManager::is_partner_failing(TransportAddress partner, int j, std::map<TransportAddress, std::vector<int>> partner_latest_blocks) {
    // check if parent is failing
    int hsjp = partner_latest_blocks[partner][j];

    // inequality 1: limiting maximum fall-behind on single substream within node
    std::set<int> abs_hsia_hsjp;
    for (int i = 0; i < substream_count; ++i) {
        if (buffers[i].size() == 0) continue;
        int hsia = buffers[i].back();
        abs_hsia_hsjp.insert(abs(hsia - hsjp));
    }
    if (abs_hsia_hsjp.size() == 0) {
        return true;
    } else {
        int max = *max_element(abs_hsia_hsjp.begin(), abs_hsia_hsjp.end());
        if (max >= ts) return true;
    }

    // inequality 2: limiting maximum fall-behind on parent substream from highest known block
    std::set<int> highest_per_partner;
    for (auto partner : partner_latest_blocks) {
        if (partner.second.size() == 0) continue;
        highest_per_partner.insert(*max_element(partner.second.begin(), partner.second.end()));
    }
    if (highest_per_partner.size() == 0) {
        return true;
    } else {
        int hsiq = *max_element(highest_per_partner.begin(), highest_per_partner.end());
        if (hsiq - hsjp >= tp) return true;
    }

    return false;
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
    auto incoming_subscriptions = buffer_map_msg->getBuffer_map().second;
    for (int ss = 0; ss < substream_count; ++ss) {
        auto entry = incoming_subscriptions.find(ss);
        if (entry != incoming_subscriptions.end()) {
            substream_children[ss].insert({buffer_map_msg->getFrom(), entry->second});
        } else {
            substream_children[ss].erase(buffer_map_msg->getFrom());
        }
    }
}

// BLOCK // UDP
// sending a block to a child partner, who then forwards it to their children
void StreamManager::send_block_message(TransportAddress child, int index, bool triggers_send) {
    Block* block = new Block();
    block->setIndex(index);
    block->setShould_trigger_send(triggers_send);
    block->setBitLength(block_size_bits);
    parent->sendMessageToUDP(child, block);
}

void StreamManager::receive_block_message(Block* block) {
    int index = block->getIndex();
    int substream_id = index % substream_count;
    auto substream = buffers[substream_id];

    // check if this is the next block in line and accept if so
    if (index == get_next_needed_block(substream_id)) {
        substream.push_back(index);
    }

    // either way push blocks to subscribers. if the block is still catching up, send two blocks
    // when we do this, that block would send four blocks, eight, sixteen etc. in turn
    // to avoid this we only allow the second block to trigger forwarding; the following node thus only sends two blocks
    if (block->getShould_trigger_send() && substream.size() > 0) {
        for (auto child_entry : substream_children[substream_id]) {
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
