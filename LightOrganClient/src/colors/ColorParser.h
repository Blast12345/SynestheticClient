#pragma once

#include "Color.h"
#include "Colors.h"
#include <Arduino.h>
#include <sstream>
#include <vector>

class ColorParser {
public:
    static auto getColor(const String &message) -> Color {
        std::vector<uint8_t> colorChannels = getColorChannels(message);
        
        if (colorChannels.size() == 3) {
            return getColor(colorChannels);
        } else {
            Serial.println("Invalid color message: " + message);
            return Colors::Black;
        }
    }

private:
    static auto getColorChannels(const String &message) -> std::vector<uint8_t> {
        std::vector<uint8_t> colorChannels;
        std::stringstream s_stream(message.c_str());
        
        for (int i; s_stream >> i;) {
            colorChannels.push_back(i);
            
            if (s_stream.peek() == ',') {
                s_stream.ignore();
            }
        }
        
        return colorChannels;
    }
    
    static auto getColor(const std::vector<uint8_t> &colorChannels) -> Color {
        return Color(colorChannels[0], colorChannels[1], colorChannels[2]);
    }
};
