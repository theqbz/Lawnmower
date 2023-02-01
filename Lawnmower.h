#pragma once
#include "Screen.h"
#include "Waypoint.h"

class Lawnmower :
    public Screen
{
    Location location;
    float    heading;
    short    battery;
    Pixel    dock;
    bool     dockInRange;
    std::vector<Waypoint*> memory;
    Waypoint* currentWaypoint;

    Location calculateDestination() const;
    Location testCalculateDestination(const Location&, const float&) const;
    Location offsetCalculation() const;
    Waypoint* setWaypoint(const Pixel&);

public:
    static unsigned long stepCounter;
    Lawnmower(const Pixel&, const Pixel&);
    ~Lawnmower();
    Location getLocation() const;
    Pixel destination() const;
    Pixel testDestination(const Location&, const float&) const;
    void newHeading();
    Location move(Pixel&);
    Location testMove(const Location&, const float&) const;
    float lineToDock() const;
    bool batteryLow() const;
    void moveToDock();
    void recharge();
    std::string getTelemetry() const;
    void printTelemetry() const;

};

