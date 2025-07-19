#include "Configuration.h"
#include "LedManager.h"
#include "FastLED.h"

CRGB leds[ledCount];

void LedManager::setup()
{
    FastLED.addLeds<NEOPIXEL, ledPin>(leds, ledCount);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 2400);
}

void LedManager::setAllTo(Color color)
{
    Serial.println("Setting pixels...");

    for (uint i = 0; i < ledCount; i++)
    {
        leds[i].setRGB(color.red, color.green, color.blue);
    }

    FastLED.show();
}

void LedManager::setLed(int index, Color color)
{

    leds[index].setRGB(color.red, color.green, color.blue);
}