#pragma once

template <typename Derived>
class SIUnit
{
private:
    const double baseValue;
    static constexpr double Milli = 1e3;

public:
    explicit SIUnit(double baseValue)
        : baseValue(baseValue) {}

    double toBase() const { return baseValue; }
    double toMilli() const { return baseValue * Milli; }
};