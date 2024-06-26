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
 	int block_index; // to synchronize playout index
}

// coolstreaming deputy partner list request message
packet GetCandidatePartnersCall extends BaseCallMessage {
	TransportAddress from;
}

packet GetCandidatePartnersResponse extends BaseResponseMessage {
 	BandwidthMap candidates;   
}

// novel "interlink" algorithm partnership split messages

packet LinkOriginNodes extends BaseOverlayMessage {
 	TransportAddress origin;
}

enum SplitResult {
	SUCCESS = 0;
	FAILED = 1;
}

packet SplitCall extends BaseCallMessage {
    int uuid; // to associate TrySplit with this SplitCall later
    bool is_switch_call; // if this was called for a scheduled switch or an entry
    TransportAddress into;
}

packet SplitResponse extends BaseResponseMessage {
    int uuid;
    bool is_switch_call;
    int result enum (SplitResult);
    TransportAddress first_node;
    TransportAddress second_node;
}

packet TrySplitCall extends BaseCallMessage {
    int uuid;
    TransportAddress into;
    TransportAddress from;
}

packet TrySplitResponse extends BaseResponseMessage {
    int uuid;
    int result enum (SplitResult);
    TransportAddress into;
    TransportAddress from;
}

packet Leave extends BaseOverlayMessage {
	TransportAddress from;
}

packet PanicMsg extends BaseOverlayMessage {
 	TransportAddress panicking;
 	TransportAddress last_hop;
    simtime_t send_time;
}

enum LastHopOpinion {
 	CAN_HELP = 0;
 	CANT_HELP = 1;   
}

packet PanicSplitMsg extends BaseOverlayMessage {
    int last_hop_opinion enum (LastHopOpinion);
    TransportAddress panicking;
    TransportAddress last_hop;
    simtime_t send_time;
}

packet PanicSplitFound extends BaseOverlayMessage {
    TransportAddress panicking;
    TransportAddress last_hop;
}

packet Recover extends BaseOverlayMessage {
 	TransportAddress helper;   
}

// self-message to track when to fail a partner connection after not receiving buffermaps for some period
message Failure {
	TransportAddress failed;   
}

// self-message to call when the node's partner network is completely collapsed and we should start over
message TotalPartnerFailure {}

// self-message to disable/enable reselection of a given substream
message Cooldown {
 	int substream;   
}

// new coolstreaming buffermap exchange, extended with partnerlink data
packet BufferMapMsg extends BaseOverlayMessage {
    TransportAddress from;
 	BufferMap buffer_map;
    TransportAddress associate;
    bool panicking;
}

// new coolstreaming block push
packet Block extends BaseOverlayMessage {
 	int index;
 	TransportAddress from;
}

// active_node finished downloading self-message/timer
message ExchangeAfterDownload {
	TransportAddress finished;   
}

// TODO: remove these
packet Partnership extends BaseOverlayMessage {
    TransportAddress from;
    int bandwidth;
}

packet PartnershipEnd extends BaseOverlayMessage {
    TransportAddress from;
}