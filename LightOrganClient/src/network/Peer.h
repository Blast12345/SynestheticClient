#pragma once

#include <esp_now.h>
#include "misc/MacAddress.h"

class Peer {
    MacAddress address;

public:
    explicit Peer(const MacAddress address) : address(address) {}
    
    auto getInfo() const -> esp_now_peer_info_t {
        esp_now_peer_info_t info{};
        
        std::copy_n(address.toBytes(), MacAddress::Octets, &info.peer_addr[0]);
        info.channel = 0;
        info.encrypt = false;
        
        return info;
    }
    
    auto getMacAddress() const -> MacAddress {
        return address;
    }
    
};
