
#include "event.h"

Event::Event()
{
  Type = EVENT_UNDEFINED;
}

Event::~Event()
{
	if( Type == EVENT_NETWORK_PACKET_RECEIVED )
	{
		enet_packet_destroy( Data.Network.Traffic.packet );
	}
}
