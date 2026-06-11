#pragma once

#include "network/EspNowAdapter.h"
#include "network/Peer.h"
#include "network/BroadcastPeer.h"

class Network {
    BroadcastPeer broadcastPeer;
    EspNowAdapter &espNow;
    
    using StringCallback = std::function<void(const String &string, const MacAddress &mac)>;
    StringCallback stringCallback;

public:
    explicit Network(StringCallback stringCallback, EspNowAdapter &espNow = EspNowAdapter::getInstance())
            : stringCallback(stringCallback), espNow(espNow) {
        espNow.initialize();
        espNow.registerDataReceivedCallback([this](auto... args) { handleData(args...); });
        espNow.addPeer(broadcastPeer);
    }

private:
    void handleData(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
        const MacAddress macAddress(mac_addr);
        Serial.println("Data received from:" + macAddress.toString());
        
        // Right now we assume everything is a string.
        String receivedString = StringHelpers::fromBytes(incomingData, len);
        Serial.println("String received: " + receivedString);
        
        stringCallback(receivedString, macAddress);
    }
    
    void addPeer(const Peer peer) {
        espNow.addPeer(peer);
    }
    
};
