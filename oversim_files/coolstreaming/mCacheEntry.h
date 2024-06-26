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

#include "../coolstreaming/Coolstreaming_m.h"
#include "../coolstreaming/MembershipManager.h"

#ifndef OVERLAY_MYOVERLAY_MCACHEENTRY_H_
#define OVERLAY_MYOVERLAY_MCACHEENTRY_H_

class mCacheEntry {
public:

    int seq_num;
    int num_partner;
    simtime_t ttl;
    simtime_t last_update_time;
    int bandwidth;

    bool expired();

    mCacheEntry(
            int s,
            int np,
            simtime_t ttl,
            int b):

            seq_num(s),
            num_partner(np),
            ttl(ttl),
            last_update_time(simTime()),
            bandwidth(b)
    {};

    ~mCacheEntry() {};

};

#endif /* OVERLAY_MYOVERLAY_MCACHEENTRY_H_ */
