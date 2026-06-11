#include <esp_now.h>

#include <utility>
#include "Peer.h"

class EspNowAdapter {
    using DataReceivedCallback = std::function<void(const uint8_t *mac_addr, const uint8_t *data, int len)>;
    
    DataReceivedCallback dataReceivedCallback;

public:
    static auto getInstance() -> EspNowAdapter & {
        static EspNowAdapter instance;
        return instance;
    }
    
    void initialize() {
        const esp_err_t result = esp_now_init();
        
        if (result == ESP_OK) {
            Serial.println("ESP-NOW initialized successfully");
        } else {
            const char *errorMessage = esp_err_to_name(result);
            Serial.println("Error initializing ESP-NOW: " + String(errorMessage));
        }
    }
    
    void registerDataReceivedCallback(DataReceivedCallback callback) {
        this->dataReceivedCallback = std::move(callback);
        
        esp_now_register_recv_cb([](auto ... args) {
            EspNowAdapter::getInstance().onDataReceived(args...);
        });
    }
    
    void addPeer(const Peer peer) {
        const esp_now_peer_info_t peerInfo = peer.getInfo();
        const esp_err_t result = esp_now_add_peer(&peerInfo);
        
        if (result == ESP_OK) {
            Serial.println("Peer added successfully");
        } else {
            const char *errorMessage = esp_err_to_name(result);
            Serial.println("Failed to add peer: " + String(errorMessage));
        }
    }

private:
    
    void onDataReceived(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
        if (dataReceivedCallback) {
            dataReceivedCallback(mac_addr, incomingData, len);
        }
    }
    
};