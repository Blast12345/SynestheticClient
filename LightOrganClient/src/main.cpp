#include "helpers/Wait.h"
#include <WiFi.h>
#include "network/Network.h"
#include "Configuration.h"
#include "colors/ColorParser.h"

#include <esp_now.h>
#include <queue>
#include <ArduinoJson.h>

constexpr unsigned DEBUG_DELAY = 5000;
constexpr unsigned WIFI_WARMUP = 1000;

Network *network;

void onMessageReceived(const String &string, const MacAddress &mac) {
    JsonDocument json;
    deserializeJson(json, string);

    // assumes its a color
    uint8_t r = json["params"]["r"];
    uint8_t g = json["params"]["g"];
    uint8_t b = json["params"]["b"];

    Color nextColor = Color(r, g, b);
    // Color nextColor = ColorParser::getColor(string);
    Serial.println("Color parsed...");
    ledChain.setAllTo(nextColor);
}

void setup() {
#ifdef DEBUG
    delay(DEBUG_DELAY);
#endif

    Serial.begin(BAUD_RATE);
    Serial.println("Baud rate set to: " + String(BAUD_RATE));

    ledChain.setup(); // ideally this should be done in the constructor, but I don't think it works that way.

    WiFi.mode(WIFI_STA); // NOLINT

    /*
     * TODO: ESP-NOW will init successfully without this, but the peer fails to add without.
     * The delay also must be directly in the setup method; including it in the constructor does not seem to work.
     * This is very strange and my research has not yielded any results. Perhaps this is a bug in the ESP-NOW library?
    */
    delay(WIFI_WARMUP);

    WiFi.mode(WIFI_STA);

    network = new Network(onMessageReceived);

    Serial.println("Setup complete.");
}

// cppcheck-suppress unusedFunction
void loop() {
    //    delay(1000);
    //    Serial.println("Looping...");
}
