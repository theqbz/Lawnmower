#pragma once
#include "Screen.h"

class Waypoint :
    public Screen
{
    Pixel coordinates;
    short distance;
    Waypoint* previous;

    void updateIcon();

public:
    Waypoint(const Pixel&, const Pixel&, Waypoint*);
    Pixel getCoordinates() const;
    short getDistance() const;
    Waypoint* getPrevious() const;
    void update(Waypoint*);
};

