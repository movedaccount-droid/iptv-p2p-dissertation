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
    Node* parent;
    std::vector<std::deque<int>> buffers; // one queue for each buffer. we don't need to sim the cache buffer
    std::vector<std::map<TransportAddress, int>> substream_children; // currently active children in each substream, and their current catch-up position
    std::vector<TransportAddress> substream_parents; // map of substream to partner

    int substream_count; // number of substreams
    int block_length_s; // block length in seconds
    int block_size_bits; // block size in bits
    int ts; // constant for maximum gap within a node's substreams
    int tp; // constant for maximum gap between a node's partners

    bool playing; // if the stream is playing
    int playout_index; // next block to be played by playout

    cMessage* exchange_timer;
    cMessage* playout_timer;

    // lifecycle
    void init(Node* p, int sc, int bls, int bsb, int ts_in, int tp_in);
    void start(int start_index);
    void reselect_partners_and_exchange(std::map<TransportAddress, std::vector<int>> partner_latest_blocks);
    void playout();
    void end();

    // utility
    int get_next_needed_block(int substream);
    int get_playout_index();
    BufferMap get_buffer_map(TransportAddress partner);
    std::vector<int> get_latest_blocks(); // returns first vector for buffer map
    std::map<int, int> get_subscription_map(TransportAddress partner); // second vector for buffer map
    bool is_partner_failing(TransportAddress partner, int j, std::map<TransportAddress, std::vector<int>> partner_latest_blocks);

    // BUFFER_MAP // UDP
    // exchange buffer_maps with peers to update local view of blocks
    // remember: exchange doesn't mean tit-for-tat!! the two nodes
    // send each other the map in their own time, by their own timer
    void send_buffer_map_message(TransportAddress partner, BufferMap buffer_map);
    // bool receive_buffer_map_latest_blocks(BufferMapMsg* buffer_map_msg) => PartnershipManager.h
    void receive_buffer_map_subscriptions(BufferMapMsg* buffer_map_msg);

    // BLOCK // UDP
    // sending a block to a child partner, who then forwards it to their children
    void send_block_message(TransportAddress child, int index, bool triggers_send);
    void receive_block_message(Block* block);

    StreamManager() { exchange_timer = NULL; playout_timer = NULL; };
    virtual ~StreamManager();
};

#endif /* OVERLAY_COOLSTREAMING_STREAMMANAGER_H_ */
