#include "Waypoint.h"

Waypoint::Waypoint(const Pixel& coordinates, const Pixel& margin, Waypoint* previous) :
    Screen(WAYPOINT_ICON, coordinates, margin, WAYPOINT_COLOR)
{
    this->coordinates = coordinates;
    this->previous = previous;
    if (previous == nullptr) distance = 0;
    else {
        distance = previous->distance + 1;
        this->updateIcon();
    }
}

Pixel Waypoint::getCoordinates() const
{
    return coordinates;
}

short Waypoint::getDistance() const
{
    return distance;
}

Waypoint* Waypoint::getPrevious() const
{
    return previous;
}

void Waypoint::update(Waypoint* waypoint)
{
    if (waypoint == nullptr) return;
    if (this == waypoint) return;
    if (this == waypoint->previous) return;
    if (waypoint == this->previous) return;
    if (notNeighbours(waypoint)) return;
    if (this->distance == waypoint->distance) return;
    if (this->distance < waypoint->distance + 1) {
        waypoint->distance = this->distance + 1;
        waypoint->update(waypoint->previous);
        waypoint->previous = this;
        waypoint->updateIcon();
        waypoint->draw();
    }
    else if (this->distance > waypoint->distance + 1) {
        this->distance = waypoint->distance + 1;
        this->update(this->previous);
        this->previous = waypoint;
        this->updateIcon();
        this->draw();
    }
}

bool Waypoint::notNeighbours(const Waypoint* waypoint) const
{
    if (abs(this->coordinates.y - waypoint->coordinates.y) > 1 ||
        abs(this->coordinates.x - waypoint->coordinates.x) > 1)
        return true;
    return false;
}

void Waypoint::updateIcon()
{
    if (pixel.x == previous->pixel.x) {
        if (pixel.y > previous->pixel.y) icon = ARROW_UP;
        else icon = ARROW_DOWN;
    }
    else if (pixel.y == previous->pixel.y) {
        if (pixel.x > previous->pixel.x) icon = ARROW_LEFT;
        else icon = ARROW_RIGHT;
    }
    else if (pixel.x > previous->pixel.x) {
        if (pixel.y > previous->pixel.y) icon = ARROW_UPLEFT;
        else icon = ARROW_DOWNLEFT;
    }
    else if (pixel.x < previous->pixel.x) {
        if (pixel.y > previous->pixel.x) icon = ARROW_UPRIGHT;
        else icon = ARROW_DOWNRIGHT;
    }
}

