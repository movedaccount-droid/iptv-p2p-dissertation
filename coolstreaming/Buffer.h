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

class Node;
class Buffer {
private:
    Node* parent; // object ... structure ..
    std::unordered_set<int> buffer; // set of block indexes we own
    int playout_interval; // duration between blocks
    int playout_index; // next block index to be played out. also the lowest block that should be in the buffer
    int buffer_size; // stored blocks in buffer. probably just 120
    int start_threshold; // percentage filled before we start playback

    cMessage* playout_timer;

    // lifecycle
    void init(Node* p, int pint, int pind, int bs, double st);
    void start();
    double percent_filled();
    void receive(int block); // receive a block
    void playout(); // playout a block

public:
    Buffer() {};
    virtual ~Buffer() { playout_timer = NULL; };
};

#endif /* OVERLAY_COOLSTREAMING_BUFFER_H_ */
