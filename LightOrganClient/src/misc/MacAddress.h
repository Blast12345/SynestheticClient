#pragma once

#include "helpers/StringHelpers.h"

class MacAddress {
public:
    static constexpr size_t Octets = 6;

private:
    std::array<uint8_t, Octets> address;

public:
    explicit MacAddress(const std::array<uint8_t, Octets> array) : address(array) {}
    
    explicit MacAddress(const uint8_t *bytes) {
        std::copy_n(bytes, Octets, address.begin());
    }
    
    constexpr auto toBytes() const noexcept -> const uint8_t * {
        return address.data();
    }
    
    auto toString() const -> String {
        std::array<String, Octets> parts;
        
        for (size_t i = 0; i < Octets; ++i) {
            const auto byte = address.at(i);
            parts.at(i) = StringHelpers::toHexString(byte);
        }
        
        return StringHelpers::join(parts, ":");
    }
};
