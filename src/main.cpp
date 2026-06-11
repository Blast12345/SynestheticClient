#include <ArduinoJson.h>
#include <WiFi.h>
#include "leds/LedChain.h"
#include "network/Network.h"

constexpr unsigned MONITOR_CONNECT_DELAY = 1000;

Network *network;
LedChain<LED_PIN> ledChain(LED_COUNT, Voltage(VOLTAGE), Amperage(AMPERAGE));

void onMessageReceived(const String &string, const MacAddress &mac) {
    JsonDocument json;
    deserializeJson(json, string);

    // assumes it is a color
    const uint8_t red = json["params"]["r"];
    const uint8_t green = json["params"]["g"];
    const uint8_t blue = json["params"]["b"];

    const auto nextColor = Color(red, green, blue);
    ledChain.setAllTo(nextColor);
}

void setup() {
    Serial.begin(BAUD_RATE);

#ifdef DEBUG
    delay(MONITOR_CONNECT_DELAY);
#endif

    Serial.println("Baud rate set to: " + String(BAUD_RATE));

    ledChain.setup();

    WiFi.mode(WIFI_STA);

    network = new Network(onMessageReceived);

    Serial.println("Setup complete.");
}

// cppcheck-suppress unusedFunction
void loop() {}
