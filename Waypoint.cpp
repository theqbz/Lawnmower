#include "Waypoint.h"

void Waypoint::updateIcon()
{
    if (this->getPixel().x == this->previous->getPixel().x) {
        if (this->getPixel().y > this->previous->getPixel().y) this->icon = ARROW_UP;
        else this->icon = ARROW_DOWN;
    }
    else if (this->getPixel().y == this->previous->getPixel().y) {
        if (this->getPixel().x > this->previous->getPixel().x) this->icon = ARROW_LEFT;
        else this->icon = ARROW_RIGHT;
    }
    else if (this->getPixel().x > this->previous->getPixel().x) {
        if (this->getPixel().y > this->previous->getPixel().y) this->icon = ARROW_UPLEFT;
        else this->icon = ARROW_DOWNLEFT;
    }
    else if (this->getPixel().x < this->previous->getPixel().x) {
        if (this->getPixel().y > this->previous->getPixel().x) this->icon = ARROW_UPRIGHT;
        else this->icon = ARROW_DOWNRIGHT;
    }
}

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
