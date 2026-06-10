#pragma once

namespace StringHelpers {
    
    static auto fromBytes(const uint8_t *bytes, int length) -> String {
        return {std::string(bytes, bytes + length).c_str()};
    }
    
    static auto toHexString(const uint8_t byte) -> String {
        String output(byte, HEX);
        output.toUpperCase();
        
        if (output.length() == 2) {
            return output;
        } else {
            return "0" + output;
        }
    }
    
    template<size_t N>
    static auto join(const std::array<String, N> &parts, const String &joiner) -> String {
        String output;
        
        for (size_t i = 0; i < N; ++i) {
            output += parts.at(i);
            
            if (i < N - 1) {
                output += joiner;
            }
        }
        
        return output;
    }
    
}
