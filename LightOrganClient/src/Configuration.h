#pragma once

#include "helpers/measurements/Amperage.h"
#include "helpers/measurements/Voltage.h"
#include "leds/LedChain.h"

// ENHANCEMENT: Do configuration from the server and persist configs between reboots

// Board
constexpr unsigned long baudRate = 115200;

// LEDs
// I'd prefer to pass this into the constructor, but FastLEDs API does not seem to make this possible.
constexpr unsigned int ledPin = 13;
constexpr unsigned int ledCount = 32;

LedChain<ledPin> ledChain(ledCount,
                          Voltage(5.0),
                          Amperage(1.0));
