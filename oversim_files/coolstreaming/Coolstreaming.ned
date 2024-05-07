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

//
// @author Antonio Zea
//


package oversim.overlay.coolstreaming;

import oversim.common.BaseOverlay;
import oversim.common.IOverlay;

simple Node extends BaseOverlay
{
    parameters:
        @class(Node);
        int c; // SCAMP constant determining proportion of tolerated failures
        int scamp_resubscription_interval; // delay before resubscriptions, sub ttl
    	int scamp_heartbeat_interval; // delay between heartbeats being sent
   	 	int scamp_heartbeat_failure_interval; // delay between received heartbeats before resubbing
   	 	
   	 	int M; // target number of partners held by a node
    	double partnership_timeout_s; // duration without receiving buffermaps before a partner connection is failed
   	 	double panic_timeout_s; // duration before gossiped panic is invalidated
   	 	double panic_split_timeout_s; // duration before gossiped panic_split is invalidated
   	 	double switch_interval_s; // delay between scoring and trying out new partners from mcache
   	 	
   	 	int exchange_interval_s; // delay between buffermap being sent
    	int reselect_cooldown_interval_s; // time before a substream can be reselected again after reselection
   	 	int buffer_size; // stored blocks in buffer. probably just 120
    	double start_threshold; // percentage filled before we start playback
   	 	
   	 	int bitrate_kbps; // video bitrate in kbps
   	 	int block_length_s; // segment length in seconds
   	 	int substream_count; // number of substreams to split video into
   	 	double partner_percentage_threshold_to_start_playout; // value of partners.size() / M to reach before surveying starting position and starting playout
   	 	
        bool origin; // if this node should act as the origin
        string first_origin_ip; // ip to contact to reach the first origin. changes regularly depending on seed...
        string second_origin_ip; // second origin. in a real system this could be a list of any length
        bool heterogeneous_upload; // if we should enable heterogenous upload. only works on inet underlay
        string arrow_type; // which arrow type to display
        string display_string; // which display string to display
        
        int ts; // constant for maximum gap within a node's substreams
        int tp; // constant for maximum gap between a node's partners
}

module NodeModules like IOverlay
{
    @display("t=...,top,blue");
    gates:
        input udpIn;   // gate from the UDP layer
        output udpOut;    // gate to the UDP layer
        input tcpIn;    // gate from the TCP layer
        output tcpOut;    // gate to the TCP layer
        input appIn;   // gate from the application
        output appOut;    // gate to the application

    submodules:
        overlay: Node;

    connections allowunconnected:
        udpIn --> overlay.udpIn;
        udpOut <-- overlay.udpOut;
        appIn --> overlay.appIn;
        appOut <-- overlay.appOut;
}
