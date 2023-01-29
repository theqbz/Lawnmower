#pragma once
#include "Screen.h"

class Lawnmower :
    public Screen
{
    Location location;
    float heading;
    unsigned short battery;
    Pixel dock;

public:
    Lawnmower(const Pixel&);
    Location calculateDestination() const;
    void calculateNewHeading();
    void moveTo(const Location&);
    bool batteryLow();
    void recharge();
};

