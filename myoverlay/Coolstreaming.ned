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


package oversim.overlay.myoverlay;

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
   	 	
   	 	int bm_exchange_interval; // delay between buffermap being sent
   	 	int M; // target number of partners held by a node
   	 	
        bool origin; // if this node should act as the origin
}

module NodeModules like IOverlay
{
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
