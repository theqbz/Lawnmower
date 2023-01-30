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
    Location offsetCalculation() const;

public:
    static unsigned long stepCounter;
    Lawnmower(const Pixel&, const Pixel&);
    Pixel destination() const;
    void newHeading();
    Location move(Pixel&);
    bool batteryLow() const;
    void recharge();
    std::string getTelemetry() const;
    void printTelemetry() const;
};

