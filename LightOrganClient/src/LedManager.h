#include "Color.h"

#pragma once

class LedManager
{
public:
    void setup();
    void setAllTo(Color color);
    void setLed(int index, Color color);

private:
};
