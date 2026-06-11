#pragma once

#include <FastLED.h>
#include "colors/Color.h"
#include "helpers/measurements/Amperage.h"
#include "helpers/measurements/Voltage.h"

template <unsigned int PIN>
class LedChain
{
private:
    CRGB *leds;
    const unsigned int ledCount;
    const Voltage voltage;
    const Amperage amperage;

public:
    LedChain(unsigned int ledCount, Voltage voltage, Amperage amperage) : ledCount(ledCount), voltage(voltage), amperage(amperage)
    {
        leds = new CRGB[ledCount];
    }

    LedChain(const LedChain &) = delete;
    LedChain &operator=(const LedChain &) = delete;

    void setup()
    {
        FastLED.addLeds<NEOPIXEL, PIN>(leds, ledCount);
        FastLED.clear(true);
        FastLED.setMaxPowerInVoltsAndMilliamps(voltage.toBase(), amperage.toMilli());
        Serial.println("LED chain initialized.");
    }

    void setAllTo(Color color)
    {
        Serial.printf("Setting pixels to R: %u, G: %u, B: %u \n", color.red, color.green, color.blue);

        for (uint i = 0; i < ledCount; i++)
        {
            leds[i].setRGB(color.red, color.green, color.blue);
        }

        FastLED.show();
    }
};
