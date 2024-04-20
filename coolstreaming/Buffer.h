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

#ifndef OVERLAY_COOLSTREAMING_BUFFER_H_
#define OVERLAY_COOLSTREAMING_BUFFER_H_

#include <unordered_set>
#include "common/TransportAddress.h"
#include "Coolstreaming_m.h"

class Node;
class Buffer {
public:
    Node* parent; // object ... structure ..
    std::unordered_set<int> buffer; // set of block indexes we own
    int playout_interval; // duration between blocks
    int playout_index; // next block index to be played out. also the lowest block that should be in the buffer
    int buffer_size; // stored blocks in buffer. probably just 120
    int block_size_bits; // size of transferred block in bits
    double start_threshold; // percentage filled before we start playback
    bool started; // if running

    cMessage* playout_timer;

    // lifecycle
    void init(Node* p, int pint, int bs, double st, int bsb);
    void set_playout_index(int pind);
    void start();
    double percent_filled();
    std::unordered_set<int> get_buffer_map();
    std::unordered_set<int> get_expected_set(); // return the "inverse" of our buffer
    int get_playout_index();
    void receive(int block); // receive a block
    void playout(); // playout a block

    // BLOCK // TCP
    // requesting and receiving blocks from partners to play
    // continuing from head function in Scheduler.h
    void receive_block_request_message_and_respond(BlockRequest* block_request);
    void receive_block_message(Block* block);

    Buffer() { playout_timer = NULL; };
    virtual ~Buffer();
};

#endif /* OVERLAY_COOLSTREAMING_BUFFER_H_ */
