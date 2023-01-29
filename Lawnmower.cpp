#include "Lawnmower.h"

Location Lawnmower::calculateDestination() const
{
    Location destination{ 0.0f,0.0f };
    destination.x = location.x + sin(heading);
    destination.y = location.y + cos(heading);
    return Location();
}

Lawnmower::Lawnmower(const Pixel& pixel) :
    Screen(LAWNMOWER_ICON, pixel, LAWNMOWER_COLOR)
{
    location.x = (float)pixel.x + 0.5f;
    location.y = (float)pixel.y + 0.5f;
    heading = PI / 2.0f;
    battery = 100;
    dock = pixel;
    dockInRange = true;
}

bool Lawnmower::batteryLow()
{
    return battery < LAWNMOWER_LOW_BATTERY;
}

std::string Lawnmower::getTelemetry() const
{
    return "loc: " + std::to_string(location.y) + "," + std::to_string(location.x)
        + "\tcell: " + std::to_string(pixel.y) + "," + std::to_string(pixel.x)
        + "\theading: " + std::to_string(heading) + " rad"
        + "\tbattery: " + std::to_string(battery) + "%";
}
