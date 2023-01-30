#include "Lawnmower.h"

unsigned long Lawnmower::stepCounter = 0;

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

Location Lawnmower::calculateDestination() const
{
    Location destination{ 0.0f,0.0f };
    destination.x = location.x + cos(heading);
    destination.y = location.y + sin(heading);
    return destination;
}

Location Lawnmower::offsetCalculation() const
{
    Location offset = { 0.0f,0.0f };
    offset.y = location.y - ((short)location.y + 0.5f);
    offset.x = location.x - ((short)location.x + 0.5f);
    return offset;
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
    bool goodHeading = false;
    while (!goodHeading) {
        short newHeading = 0 + (rand() % 360);
        if (newHeading % 180 != ((short)((180*heading)/PI)) % 180) {
            heading = (PI * (float)newHeading) / 180;
            goodHeading = true;
        }
    }
}

Location Lawnmower::move(Pixel& destinationPixel)
{
    location = calculateDestination();
    pixel.reciveLocation(location);
    battery--;
    stepCounter++;
    destinationPixel = pixel;
    return offsetCalculation();
}

bool Lawnmower::batteryLow() const
{
    if (battery < LAWNMOWER_LOW_BATTERY) return true;
    else return false;
}

void Lawnmower::recharge()
{
    battery = 100;
}

std::string Lawnmower::getTelemetry() const
{

    return
        "batt: " + std::to_string(battery) + "%"
        + "\thead: " + std::to_string((short)((180 * heading) / PI)) + char(248)
        + "\tcell: " + std::to_string(pixel.y) + "," + std::to_string(pixel.x)
        + "\tloc: " + std::to_string(location.y) + "," + std::to_string(location.x);
}

void Lawnmower::printTelemetry() const
{
    std::cout << "TELEMETRY\n"
        << "\nbattery:\n" << std::setprecision(3) << battery << "%"
        << "\ncell:\n" << pixel.x << ", " << pixel.y
        << "\nheading:\n" << (short)((180 * heading) / PI) << char(248)
        << "\nlocation:\n" << std::setprecision(4) << location.x << "," << location.y
        << "\nmoves:\n" << stepCounter;
}
