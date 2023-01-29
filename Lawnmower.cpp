#include "Lawnmower.h"

Location Lawnmower::calculateDestination() const
{
    Location destination{ 0.0f,0.0f };
    destination.x = location.x + sin(heading);
    destination.y = location.y + cos(heading);
    return destination;
}

Lawnmower::Lawnmower(const Pixel& pixel, const Pixel& margin) :
    Screen(LAWNMOWER_ICON, pixel, margin, LAWNMOWER_COLOR)
{
    location.x = (float)pixel.x + 0.5f;
    location.y = (float)pixel.y + 0.5f;
    heading = PI / 2.0f;
    battery = 100;
    dock = pixel;
    dockInRange = true;
}

Pixel Lawnmower::destination() const
{
    Location destination = calculateDestination();
    Pixel pixel = { 0,0 };
    pixel.x = (short)destination.x;
    pixel.y = (short)destination.y;
    return pixel;
}

void Lawnmower::newHeading()
{
    short newHeading = 0;
    bool goodHeading = false;
    while (!goodHeading) {
        newHeading = 0 + (rand() % (short)(2 * PI));
        if (newHeading % 180 != (short)heading % 180) goodHeading = true;
    }
    heading = (float)newHeading;
}

Location Lawnmower::move(Pixel& destinationPixel)
{
    Location destination = calculateDestination();
    location = destination;
    battery--;
    pixel.y = destinationPixel.y = (short)location.y;
    pixel.x = destinationPixel.x = (short)location.x;
    Location offset = { 0.0f,0.0f };
    offset.y = location.y - ((short)location.y + 0.5f);
    offset.x = location.x - ((short)location.x + 0.5f);
    draw();
    return offset;
}

bool Lawnmower::batteryLow()
{
    if (battery < 30) return true;
    else return false;
}

void Lawnmower::recharge()
{
    battery = 100;
}

std::string Lawnmower::getTelemetry() const
{
    return "loc: " + std::to_string(location.y) + "," + std::to_string(location.x)
        + "\tcell: " + std::to_string(pixel.y) + "," + std::to_string(pixel.x)
        + "\theading: " + std::to_string(heading) + " rad"
        + "\tbattery: " + std::to_string(battery) + "%";
}
