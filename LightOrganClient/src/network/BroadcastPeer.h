#pragma once

#include "network/Peer.h"

class BroadcastPeer : public Peer {
    inline static const auto BroadcastAddress = MacAddress({0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF});

public:
    BroadcastPeer() : Peer(BroadcastAddress) {}
    
};
