#include "Lawnmower.h"

unsigned long Lawnmower::stepCounter = 0;

Lawnmower::Lawnmower(const Pixel& dockPixel, const Pixel& margin) :
    Screen(LAWNMOWER_ICON, dockPixel, margin, LAWNMOWER_COLOR)
{
    location.x = (float)dockPixel.x + 0.5f;
    location.y = (float)dockPixel.y + 0.5f;
    heading = PI / 2.0f;
    battery = 1000;
    dock = dockPixel;
    lowBattery = false;
    currentWaypoint = new Waypoint(dockPixel, Screen::memoryOffset, nullptr);
    memory.push_back(currentWaypoint);
}

Lawnmower::~Lawnmower()
{
    for (int m = 0; m < memory.size(); m++) delete memory[m];
}

Location Lawnmower::getLocation() const
{
    return location;
}

short Lawnmower::getBatteryLevel() const
{
    return battery;
}

Location Lawnmower::calculateDestination() const
{
    Location destination{ 0.0f,0.0f };
    destination.x = location.x + cos(heading);
    destination.y = location.y + sin(heading);
    return destination;
}

Location Lawnmower::testCalculateDestination(const Location& testLocation, const float& testHeading) const
{
    Location destination{ 0.0f,0.0f };
    destination.x = testLocation.x + cos(testHeading);
    destination.y = testLocation.y + sin(testHeading);
    return destination;
}

Location Lawnmower::offsetCalculation() const
{
    Location offset = { 0.0f,0.0f };
    offset.y = location.y - ((short)location.y + 0.5f);
    offset.x = location.x - ((short)location.x + 0.5f);
    return offset;
}

Waypoint* Lawnmower::setWaypoint(const Pixel& pixel)
{
    for (int p = 0; p < memory.size(); p++) {
        if (pixel == memory[p]->getCoordinates()) {
            memory[p]->update(currentWaypoint);
            return memory[p];
        }
    }
    memory.push_back(new Waypoint(pixel, Screen::memoryOffset, currentWaypoint));
    return memory.back();
}

Pixel Lawnmower::destination() const
{
    Location destination = calculateDestination();
    Pixel pixel = { 0,0 };
    pixel.reciveLocation(destination);
    return pixel;
}

Pixel Lawnmower::testDestination(const Location& testLocation, const float& testHeading) const
{
    Location destination = testCalculateDestination(testLocation, testHeading);
    Pixel pixel = { 0,0 };
    pixel.reciveLocation(destination);
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
    currentWaypoint = setWaypoint(pixel);
    currentWaypoint->draw();
    if (currentWaypoint->getDistance() + 10 > battery) lowBattery = true;
    destinationPixel = pixel;
    return offsetCalculation();
}

Location Lawnmower::testMove(const Location& testLocation, const float& testHeading) const
{
    return testCalculateDestination(testLocation, testHeading);
}

float Lawnmower::lineToDock() const
{
    if (pixel.x == dock.x) {
        if (pixel.y > dock.y) return (3.0f * PI) / 2.0f;
        if (pixel.y < dock.y) return PI / 2.0f;
    }
    if (pixel.y == dock.y) {
        if (pixel.x > dock.x) return PI;
        if (pixel.x < dock.x) return 0.0f;
    }
    if (pixel.x > dock.x) return (float)atan((location.y - (dock.y + 0.5)) / (location.x - (dock.x + 0.5))) + PI;
    if (pixel.x < dock.x) return (float)atan((location.y - (dock.y + 0.5)) / (location.x - (dock.x + 0.5)));
}

bool Lawnmower::batteryLow() const
{
    return lowBattery;
}

void Lawnmower::trackBack()
{
    location.y = (float)currentWaypoint->getCoordinates().y + 0.5f;
    location.x = (float)currentWaypoint->getCoordinates().x + 0.5f;
    pixel.reciveLocation(location);
    currentWaypoint = currentWaypoint->getPrevious();
    battery--;
    stepCounter++;
    draw();
}

bool Lawnmower::batteryEmpty() const
{
    return battery < 1;
}

void Lawnmower::moveToDock()
{
    heading = lineToDock();
    location = calculateDestination();
    pixel.reciveLocation(location);
    battery--;
    stepCounter++;
}

void Lawnmower::recharge()
{
    battery = 1000;
}

void Lawnmower::printTelemetry() const
{
    std::cout << "TELEMETRY\n"
        << "\nbattery:\n" << std::setprecision(3) << battery / 10 << "%"
        << "\ncell:\n" << pixel.x << ", " << pixel.y
        << "\nheading:\n" << (short)((180 * heading) / PI) << char(248)
        << "\nlocation:\n" << std::setprecision(4) << location.x << "," << location.y
        << "\nmoves:\n" << stepCounter;
}
