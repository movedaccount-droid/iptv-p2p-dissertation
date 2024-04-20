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

#include "common/TransportAddress.h"
#include <unordered_set>

#ifndef OVERLAY_MYOVERLAY_PARTNERENTRY_H_
#define OVERLAY_MYOVERLAY_PARTNERENTRY_H_

class PartnerEntry {
public:
    int sent;
    int retrieved;
    simtime_t start;
    double bandwidth;
    std::vector<int> latest_blocks;

    double score() const {
        double time_units = (simTime() - start).dbl();
        double sji = sent / time_units;
        double sij = retrieved / time_units;
        return std::max(sji, sij);
    };

    // TODO: this
    void add_sent();
    void add_retrieved();

    friend bool operator<(const PartnerEntry& l, const PartnerEntry& r);

    PartnerEntry(double b, int substream_count):
        sent(0),
        retrieved(0),
        start(simTime()),
        bandwidth(b),
        latest_blocks(substream_count, 0)
    {};

    virtual ~PartnerEntry() {};
};

#endif /* OVERLAY_MYOVERLAY_PARTNERENTRY_H_ */
