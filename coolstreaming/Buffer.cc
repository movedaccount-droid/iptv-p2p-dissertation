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

#include "../coolstreaming/Buffer.h"
#include "../coolstreaming/Node.h"

#define setOrReplace(timer, name, offset) if (timer != NULL && timer->isScheduled()) { \
    parent->cancelEvent(timer); \
} else if (!timer) { \
    timer = new cMessage(name); \
} \
parent->scheduleAt(simTime() + offset, timer)

void Buffer::init(Node* p, int pint, int bs, double st, int bsb) {
    parent = p;
    playout_interval = pint;
    buffer_size = bs;
    start_threshold = st;
    block_size_bits = bsb;
    // we act as if the stream has been running a while
    if (parent->origin) {
        playout_index = 100;
        for (int all_blocks = playout_index; all_blocks < buffer_size; ++all_blocks) {
            buffer.insert(all_blocks);
        }
        start();
    }
}

void Buffer::set_playout_index(int pind) {
    if (parent->origin) return;
    playout_index = pind;
}

void Buffer::start() {
    started = true;
    playout();
}

double Buffer::percent_filled() {
    return buffer.size() / buffer_size;
}

std::unordered_set<int> Buffer::get_buffer_map() {
    return buffer;
}

std::unordered_set<int> Buffer::get_expected_set() {
    std::unordered_set<int> expected_set;
    for (int i = playout_index; i < playout_index + buffer_size; ++i) {
        if (buffer.find(i) == buffer.end()) {
            expected_set.insert(i);
        }
    }
    return expected_set;
}

int Buffer::get_playout_index() {
    return playout_index;
}

void Buffer::receive(int block) {
    if (buffer.find(block) != buffer.end()) {
        // TODO: this block was wasted. stats or whatever
    }
    if (block >= playout_index && block < playout_index + buffer_size) {
        buffer.insert(block);
    }
    if (!started && percent_filled() >= start_threshold) start();
}

void Buffer::playout() {
    if (!parent->origin) {
        if (buffer.find(playout_index) != buffer.end()) {
            // TODO: block was not present. stats
        } else {
            // TODO: block was present. stats
        }
    }
    buffer.erase(playout_index);
    playout_index++;
    // origin always has full buffer
    if (parent->origin) buffer.insert(playout_index + buffer_size - 1);
    setOrReplace(playout_timer, "playout_timer", playout_interval);
}

// BLOCK // TCP
// requesting blocks from partners to play
// extended from main functions in Scheduler.h
void Buffer::receive_block_request_message_and_respond(BlockRequest* block_request) {
    for (int requested_block : block_request->getBlocks()) {
        if (buffer.find(requested_block) != buffer.end()) {
            Block* block = new Block();
            block->setIndex(requested_block);
            block->setBitLength(block_size_bits);
            parent->sendMessageToUDP(block_request->getFrom(), block);
        }
    }
}

void Buffer::receive_block_message(Block* block) {
    buffer.insert(block->getIndex());
}

Buffer::~Buffer() {
    if (playout_timer != NULL) parent->cancelAndDelete(playout_timer);
}
