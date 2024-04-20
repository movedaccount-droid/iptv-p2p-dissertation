//
// Copyright (C) 2009 Institut fuer Telematik, Universitaet Karlsruhe (TH)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

// @author Antonio Zea

cplusplus {{
#include <chrono>
#include <set>
#include <unordered_set>
#include "common/NodeHandle.h"
#include "common/OverlayKey.h"
#include "common/CommonMessages_m.h"
#include "common/TransportAddress.h"
typedef std::chrono::duration<int,std::milli> duration_ms;
typedef std::map<TransportAddress, double> BandwidthMap;
typedef std::pair<std::vector<int>, std::map<int, int>> BufferMap;
}}
class noncobject NodeHandle;
class noncobject OverlayKey;
class noncobject TransportAddress;
class noncobject duration_ms;
class noncobject BandwidthMap;
class noncobject BufferMap;

class BaseOverlayMessage;
class BaseCallMessage;
class BaseResponseMessage;

// scamp/mcache membership message
packet Membership extends BaseOverlayMessage {
    int uuid; // to identify infinitely looping messages
    int seq_num;
    TransportAddress tad;
    int num_partner;
    simtime_t ttl;
    double bandwidth; // we need this later for scheduler calculations
    bool forwarded; // if this was forwarded or is the entry message for the node
    bool entry; // if this is the entry message for the node
}

// scamp/inview membership message
packet InviewCall extends BaseCallMessage {
    TransportAddress destination;
    TransportAddress accepting_node;
}

// scamp/inview insertion acknowledgement
packet InviewResponse extends BaseResponseMessage {}

// scamp/mcache unsubscription message
packet Unsubscription extends BaseOverlayMessage {
    TransportAddress leaving;
	TransportAddress replacement;
	bool inview;
}

// scamp/mcache heartbeat message
packet Heartbeat extends BaseOverlayMessage {}

// coolstreaming origin deputy list request message. no longer contains the starting block index as of new coolstreaming
packet GetDeputyCall extends BaseCallMessage {
	TransportAddress dest;
}

packet GetDeputyResponse extends BaseResponseMessage {
 	TransportAddress deputy;
}

// coolstreaming deputy partner list request message
packet GetCandidatePartnersCall extends BaseCallMessage {
	TransportAddress from;
}

packet GetCandidatePartnersResponse extends BaseResponseMessage {
 	BandwidthMap candidates;   
}

// coolstreaming partnership initiation/ending
packet Partnership extends BaseOverlayMessage {
	TransportAddress from;
	double bandwidth;
}

packet PartnershipEnd extends BaseOverlayMessage {
    TransportAddress from;
}

// new coolstreaming buffermap exchange
packet BufferMapMsg extends BaseOverlayMessage {
    TransportAddress from;
 	BufferMap buffer_map;
}

// new coolstreaming block push
// when we send two blocks to catch up a node, that block would send four blocks in turn, eight, sixteen etc.
// to avoid this we only allow the second block to trigger forwarding; the following node thus only sends two blocks
packet Block extends BaseOverlayMessage {
 	int index;
 	bool triggers_send;
}