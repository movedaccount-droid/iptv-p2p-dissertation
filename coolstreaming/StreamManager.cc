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
void StreamManager::init(Node* p, int sc, int eis, int rcis, int bs, int bls, int bsb, int ts_in, int tp_in, double ppttsp, bool ds) {
    parent = p;
    substream_count = sc;
    exchange_interval_s = eis;
    reselect_cooldown_interval = SimTime(rcis, SIMTIME_S);
    buffer_size = bs;
    block_length_s = bls;
    block_size_bits = bsb;
    playing = false;
    playout_index = 0;
    ts = ts_in;
    tp = tp_in;
    partner_percentage_threshold_to_start_playout = ppttsp;
    display_string = ds;
    substream_children = std::vector<std::map<TransportAddress, int>>(substream_count, std::map<TransportAddress, int>());
    substream_parents = std::vector<TransportAddress>(substream_count, TransportAddress());
    reselect_cooldown = std::vector<Cooldown*>(substream_count, NULL);

    hit_playouts = 0;
    missed_playouts = 0;
    received_blocks = 0;
    duplicate_blocks = 0;
    oob_blocks = 0;

    buffers = std::set<int>();
    if (parent->origin) {
        // origin buffers are always filled and running
        playout_index = 1000; // we act as though the stream has been playing a while
        for (int block = playout_index; block < playout_index + buffer_size; ++block) {
            buffers.insert(block);
        }
        for (int max_block = playout_index + buffer_size - substream_count; max_block < playout_index + buffer_size; ++max_block) {
            latest_blocks.push_back(max_block);
        }
        start(playout_index);
    } else {
        latest_blocks = std::vector<int>(substream_count, -1);
    }
    setOrReplace(exchange_timer, "exchange_timer", exchange_interval_s);
}

bool StreamManager::should_start(double partner_percentage) {
    return !playing && partner_percentage >= partner_percentage_threshold_to_start_playout;
}

void StreamManager::start(int start_index) {
    playout_index = start_index;
    playing = true;
    playout();
}

void StreamManager::reselect_parents_and_exchange_partners(std::map<TransportAddress, std::vector<int>> partner_latest_blocks,
        std::map<TransportAddress, TransportAddress> associations, bool panicking) {
    parent->getParentModule()->getParentModule()->bubble(std::string("exchanging...").c_str());
    if (!parent->origin && playing) {

        // we might be reselecting parents because we're no longer partners with them at all.
        // in that case we should send them one last hail mary buffermap to end our subscription,
        // else if they're still alive they will send us blocks Forever

        std::set<TransportAddress> removed_parents = reselect_parents(partner_latest_blocks);
        for (TransportAddress parent : removed_parents) {
            // TODO: sending the unassociated transportaddress here is Very Bad
            // send_buffer_map_message(parent, TransportAddress(), panicking);
        }
    }
    for (auto partner : associations) {
        send_buffer_map_message(partner.first, partner.second, panicking);
    }
    setOrReplace(exchange_timer, "exchange_timer", exchange_interval_s);
}

// returns set of removed parents
std::set<TransportAddress> StreamManager::reselect_parents(std::map<TransportAddress, std::vector<int>> partner_latest_blocks) {
    std::set<TransportAddress> removed_parents;
    for (int ss = 0; ss < substream_count; ++ss) {
        TransportAddress parent = substream_parents[ss];
        if (reselect_cooldown[ss] == NULL
                && (parent.isUnspecified()
                || partner_latest_blocks.find(parent) == partner_latest_blocks.end()
                || is_parent_failing(parent, ss, partner_latest_blocks))) {
            // get random parent as replacement
            std::vector<TransportAddress> random_candidate;
            for (auto candidate : partner_latest_blocks) {
                random_candidate.push_back(candidate.first);
            }
            std::random_device ran;
            std::mt19937 rng(ran());
            std::shuffle(random_candidate.begin(), random_candidate.end(), rng);
            for (TransportAddress candidate : random_candidate) {
                if (!is_parent_failing(candidate, ss, partner_latest_blocks, true)) {
                    this->parent->set_arrow(parent, "STREAM", false);
                    this->parent->set_arrow(candidate, "STREAM", true);
                    this->parent->getParentModule()->getParentModule()->bubble(std::string("switched to parent ")
                        .append(candidate.getIp().str())
                        .append(" on substream ")
                        .append(std::to_string(ss))
                        .append("...").c_str());
                    if (!parent.isUnspecified() && partner_latest_blocks.find(parent) == partner_latest_blocks.end()) removed_parents.insert(parent);
                    substream_parents[ss] = candidate;
                    set_cooldown(ss);
                    break;
                }
            }
        }
    }
    return removed_parents;
}

void StreamManager::playout() {
    setOrReplace(playout_timer, "playout_timer", block_length_s);
    setOrReplace(catchup_timer, "catchup_timer", block_length_s / 2.0);
    int ss = playout_index % substream_count;
    if (parent->origin) {
        parent->getParentModule()->getParentModule()->bubble(std::string("injecting new blocks...").c_str());
        buffers.erase(playout_index);
        latest_blocks[ss] += substream_count;
        buffers.insert(latest_blocks[ss]);
        push_substream_blocks_to_subscribers(ss);
    } else {
        // TODO: nodes probably can get Very Fucked Up in bad cases. but we might not have the deadline space to fix that....
        if (buffers.erase(playout_index)) {
            hit_playouts++;
        } else {
            parent->getParentModule()->getParentModule()->bubble(std::string("[!] missed playout...").c_str());
            missed_playouts++;
        }
    }
    playout_index++;
    update_display_string();
}

void StreamManager::catchup_children() {
    push_substream_blocks_to_subscribers(playout_index % substream_count);
}

void StreamManager::leave_overlay() {
    parent->add_std_dev("!StreamManager: hit_playouts", hit_playouts);
    parent->add_std_dev("!StreamManager: missed_playouts", missed_playouts);
    parent->add_std_dev("!StreamManager: received_blocks", received_blocks);
    parent->add_std_dev("!StreamManager: duplicate_blocks", duplicate_blocks);
    parent->add_std_dev("!StreamManager: oob_blocks", oob_blocks);
    playing = false;
    if (exchange_timer != NULL) parent->cancelAndDelete(exchange_timer); exchange_timer = NULL;
    if (playout_timer != NULL) parent->cancelAndDelete(playout_timer); playout_timer = NULL;
    if (catchup_timer != NULL) parent->cancelAndDelete(catchup_timer); catchup_timer = NULL;
}

// utility
void StreamManager::update_display_string() {
    int ratio = hit_playouts + missed_playouts > 0 ? (100 * hit_playouts) / (100 * (hit_playouts + missed_playouts)) : 0;
    int pc = 0;
    for (TransportAddress parent : substream_parents) {
        if (!parent.isUnspecified()) pc++;
    }
    int cc = 0;
    for (auto ss : substream_children) {
        cc += ss.size();
    }
    if (display_string) {
        display_name = std::string("PI: ")
            .append(std::to_string(playout_index))
            .append(", Ratio: ")
            .append(std::to_string(ratio))
            .append(", Parents: ")
            .append(std::to_string(pc))
            .append(", Children: ")
            .append(std::to_string(cc))
            .append("\n[");
        for (int latest : latest_blocks) {
            display_name.append(std::to_string(latest));
            display_name.append(" ");
        }
        display_name.append("]");
        cDisplayString& ds = parent->getParentModule()->getParentModule()->getDisplayString();
        ds.setTagArg("t", 0, display_name.c_str());
        ds.setTagArg("t", 2, "purple");
    }
}

int StreamManager::get_next_needed_block(int substream) {
    if (latest_blocks[substream] == -1 || latest_blocks[substream] < playout_index) {
        // manually calculate the correct block
        int current_substream_id = playout_index % substream_count;
        int diff = substream - current_substream_id;
        if (diff < 0) diff += substream_count;
        return playout_index + diff;
    } else {
        return latest_blocks[substream] + substream_count;
    }
}

int StreamManager::get_playout_index() {
    return playout_index;
}

BufferMap StreamManager::get_buffer_map(TransportAddress partner) {
    return std::make_pair(latest_blocks, get_subscription_map(partner));
}

std::map<int, int> StreamManager::get_subscription_map(TransportAddress partner) {
    std::map<int, int> subscription_map;
    for (int ss = 0; ss < substream_count; ++ss) {
        if (!substream_parents[ss].isUnspecified() && substream_parents[ss] == partner) {
            subscription_map.insert({ss, get_next_needed_block(ss)});
        }
    }
    return subscription_map;
}

bool StreamManager::is_parent_failing(TransportAddress parent, int j, std::map<TransportAddress, std::vector<int>> partner_latest_blocks, bool local_node_compromised) {
    // check if parent is failing
    int hsjp = partner_latest_blocks[parent][j];

    // inequality 1: limiting maximum fall-behind on single substream within node
    // the specification claims a new parent must satisfy these inequalities. however, inequality 1 relies on our own node's health.
    // since we're reselecting, we can assume our own node is not a good measure! so we only run the second inequality
    if (!local_node_compromised) {
        std::set<int> abs_hsia_hsjp;
        for (int ss = 0; ss < substream_count; ++ss) {
            int hsia = latest_blocks[ss];
            abs_hsia_hsjp.insert(abs(hsia - hsjp));
        }
        if (abs_hsia_hsjp.size() > 0) {
            int max = *max_element(abs_hsia_hsjp.begin(), abs_hsia_hsjp.end());
            if (max >= ts) return true;
        }
    }

    // inequality 2: limiting maximum fall-behind on parent substream from highest known block
    if (partner_latest_blocks.size() > 0) {
        std::set<int> highest_per_partner;
        for (auto parent : partner_latest_blocks) {
            highest_per_partner.insert(*max_element(parent.second.begin(), parent.second.end()));
        }
        int hsiq = *max_element(highest_per_partner.begin(), highest_per_partner.end());
        if (hsiq - hsjp >= tp) return true;
    }

    return false;
}

// cooldowns
void StreamManager::set_cooldown(int substream) {
    Cooldown* cooldown = new Cooldown();
    cooldown->setSubstream(substream);
    reselect_cooldown[substream] = cooldown;
    parent->scheduleAt(simTime() + reselect_cooldown_interval, cooldown);
}

void StreamManager::remove_cooldown(Cooldown* cooldown) {
    reselect_cooldown[cooldown->getSubstream()] = NULL;
    delete cooldown;
}

// BUFFER_MAP // UDP
// exchange buffer_maps with peers to update local view of blocks
// remember: exchange doesn't mean tit-for-tat!! the two nodes
// send each other the map in their own time, by their own timer
void StreamManager::send_buffer_map_message(TransportAddress partner, TransportAddress associate, bool panicking) {
    BufferMapMsg* buffer_map_msg = new BufferMapMsg();
    buffer_map_msg->setFrom(parent->getThisNode());
    buffer_map_msg->setBuffer_map(get_buffer_map(partner));
    buffer_map_msg->setAssociate(associate);
    buffer_map_msg->setPanicking(panicking);
    parent->sendMessageToUDP(partner, buffer_map_msg);
}

void StreamManager::receive_buffer_map_message(BufferMapMsg* buffer_map_msg) {
    auto incoming_subscriptions = buffer_map_msg->getBuffer_map().second;
    for (int ss = 0; ss < substream_count; ++ss) {
        auto entry = incoming_subscriptions.find(ss);
        if (entry != incoming_subscriptions.end()) {
            if (substream_children[ss].find(buffer_map_msg->getFrom()) == substream_children[ss].end()) {
                if (buffer_map_msg->getFrom().getIp().str() == std::string("1.0.0.10")) {
                    std::cout << "    + " << ss << " " << parent->getThisNode().getIp().str() << std::endl;
                }
            }
            substream_children[ss].insert({buffer_map_msg->getFrom(), entry->second});
        } else {
            int temp = substream_children[ss].erase(buffer_map_msg->getFrom());
            if (temp == 1) {
                if (buffer_map_msg->getFrom().getIp().str() == std::string("1.0.0.10")) {
                    std::cout << "    - " << ss << " " << parent->getThisNode().getIp().str() << std::endl;
                }
            }
        }
    }
    update_display_string();
}

// BLOCK // UDP
// sending a block to a child partner, who then forwards it to their children
void StreamManager::push_substream_blocks_to_subscribers(int ss) {
    for (auto it = substream_children[ss].begin(); it != substream_children[ss].end(); ++it) {
        // TODO: what if a child completely falls behind?
        if (buffers.find(it->second) != buffers.end()) {
            send_block_message(it->first, it->second);
            it->second += substream_count;
        }
    }
}

void StreamManager::send_block_message(TransportAddress child, int index) {
    Block* block = new Block();
    block->setIndex(index);
    block->setFrom(parent->getThisNode());
    block->setBitLength(block_size_bits);
    parent->sendMessageToUDP(child, block);
}

void StreamManager::receive_block_message(Block* block) {
    // the presentation on coolstreaming suggests nodes can rearrange blocks in their
    // buffers at will, so we can take any block at any time, provided it fits our limit
    int block_index = block->getIndex();
    int ss = block_index % substream_count;
    if (block_index < playout_index || block_index > playout_index + buffer_size) {
        if (parent->getThisNode().getIp().str() == std::string("1.0.0.10")) {
            std::cout << parent->getThisNode().getIp().str()
                        << ": received out-of-bounds block " << block_index
                        << " from " << block->getFrom().getIp().str()
                        << ((block_index >= playout_index) ? " (too high)" : " (too low)")
                        << std::endl;
        }

        oob_blocks++;
    } else if (buffers.find(block_index) == buffers.end()) {
        if (parent->getThisNode().getIp().str() == std::string("1.0.0.10")) {
            std::cout << parent->getThisNode().getIp().str()
                    << ": received " << block_index
                    << " from " << block->getFrom().getIp().str()
                    << "..." << std::endl;
        }
        if (block_index > latest_blocks[ss]) latest_blocks[ss] = block_index;
        buffers.insert(block_index);
        received_blocks++;
    } else {
        if (parent->getThisNode().getIp().str() == std::string("1.0.0.10")) {
            std::cout << parent->getThisNode().getIp().str()
                    << ": received " << block_index
                    << " from " << block->getFrom().getIp().str()
                    << " more than once..." << std::endl;
        }
        duplicate_blocks++;
    }
    // either way push blocks to subscribers.
    push_substream_blocks_to_subscribers(ss);
    update_display_string();
}


StreamManager::~StreamManager() {
    if (exchange_timer != NULL) parent->cancelAndDelete(exchange_timer); exchange_timer = NULL;
    if (playout_timer != NULL) parent->cancelAndDelete(playout_timer); playout_timer = NULL;
    if (catchup_timer != NULL) parent->cancelAndDelete(catchup_timer); catchup_timer = NULL;
}
