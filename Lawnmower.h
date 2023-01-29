#pragma once
#include "Screen.h"

class Lawnmower :
    public Screen
{
    Location location;
    float    heading;
    short    battery;
    Pixel    dock;
    bool     dockInRange;
    Location calculateDestination() const;

public:
    Lawnmower(const Pixel&);
    Pixel destination() const;
    void newHeading();
    void moveTo(const Location&);
    bool batteryLow();
    void recharge();
    std::string getTelemetry() const;
};

