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

#ifndef OVERLAY_COOLSTREAMING_STREAMMANAGER_H_
#define OVERLAY_COOLSTREAMING_STREAMMANAGER_H_

#include <unordered_set>
#include <deque>
#include "common/TransportAddress.h"
#include "Coolstreaming_m.h"

// vec of latest received in each substream,
// map of each substreams we are subscribed to and the block we want to start from
typedef std::pair<std::vector<int>, std::map<int, int>> BufferMap;

class Node;
class StreamManager {
public:
    // params
    Node* parent;
    int substream_count; // number of substreams
    int exchange_interval_s; // time between buffermap sends
    int buffer_size; // max length of the buffer. this should only be needed by the origin since nodes are semi-synchronized
    int block_length_s; // block length in seconds
    int block_size_bits; // block size in bits
    int ts; // constant for maximum gap within a node's substreams
    int tp; // constant for maximum gap between a node's partners
    double partner_percentage_threshold_to_start_playout; // value of partners.size() / M to reach before surveying starting position and starting playout
    bool display_string; // whether to show streammanager display strings

    // vars
    std::set<int> buffers; // since the blocks in the buffer are "reordered on arrival", they act closer to a set than a buffer, though we ensure we cap the total buffer size
    std::vector<int> latest_blocks; // latest block received in each buffer, stored even after the block is played out
    std::vector<std::map<TransportAddress, int>> substream_children; // currently active children in each substream, and their current catch-up position
    std::vector<TransportAddress> substream_parents; // map of substream to partner
    std::string display_name; // cached display name
    bool playing; // if the stream is playing
    int playout_index; // next block to be played by playout

    // timers
    cMessage* exchange_timer;
    cMessage* playout_timer;
    cMessage* catchup_timer;

    // stats
    int hit_playouts;
    int missed_playouts;
    int received_blocks;
    int duplicate_blocks;
    int oob_blocks;

    // lifecycle
    void init(Node* p, int sc, int eis, int bs, int bls, int bsb, int ts_in, int tp_in, double ppttsp, bool ds);
    bool should_start(double partner_percentage);
    void start(int start_index);
    void reselect_parents_and_exchange_partners(std::map<TransportAddress, std::vector<int>> parent_latest_blocks,
            std::map<TransportAddress, TransportAddress> associations, bool panicking);
    void reselect_parents(std::map<TransportAddress, std::vector<int>> parent_latest_blocks);
    void playout();
    void catchup_children();
    void leave_overlay();

    // utility
    void update_display_string();
    int get_next_needed_block(int substream);
    int get_playout_index();
    BufferMap get_buffer_map(TransportAddress parent);
    std::map<int, int> get_subscription_map(TransportAddress partner); // second vector for buffer map
    bool is_parent_failing(TransportAddress parent, int j, std::map<TransportAddress, std::vector<int>> parent_latest_blocks, bool local_node_compromised = false);

    // BUFFER_MAP // UDP
    // exchange buffer_maps with peers to update local view of blocks
    // remember: exchange doesn't mean tit-for-tat!! the two nodes
    // send each other the map in their own time, by their own timer
    void send_buffer_map_message(TransportAddress partner, TransportAddress associate, bool panicking);
    // bool receive_buffer_map_latest_blocks(BufferMapMsg* buffer_map_msg) => PartnershipManager.h
    void receive_buffer_map_message(BufferMapMsg* buffer_map_msg);

    // BLOCK // UDP
    // sending a block to a child partner, who then forwards it to their children
    void push_substream_blocks_to_subscribers(int substream);
    void send_block_message(TransportAddress child, int index);
    void receive_block_message(Block* block);

    StreamManager() { exchange_timer = NULL; playout_timer = NULL; catchup_timer = NULL; };
    virtual ~StreamManager();
};

#endif /* OVERLAY_COOLSTREAMING_STREAMMANAGER_H_ */
