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
    Location testCalculateDestination(const Location&, const float&) const;
    Location offsetCalculation() const;

public:
    static unsigned long stepCounter;
    Lawnmower(const Pixel&, const Pixel&);
    Location getLocation() const;
    Pixel destination() const;
    Pixel testDestination(const Location&, const float&) const;
    void newHeading();
    Location move(Pixel&);
    Location testMove(const Location&, const float&) const;
    float lineToDock() const;
    bool batteryLow() const;
    bool batteryEmpty() const;
    void moveToDock();
    void recharge();
    void printTelemetry() const;
};

