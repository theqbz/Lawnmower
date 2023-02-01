#include "Waypoint.h"

bool Waypoint::notNeighbours(const Waypoint* waypoint) const
{
    if (abs(this->coordinates.y - waypoint->coordinates.y) > 1 ||
        abs(this->coordinates.x - waypoint->coordinates.x) > 1)
        return true;
    return false;
}

void Waypoint::updateIcon()
{
    if (this->getPixel().x == this->previous->getPixel().x) {
        if (this->getPixel().y == this->previous->getPixel().y + 1) this->icon = ARROW_UP;
        else if (this->getPixel().y > this->previous->getPixel().y + 1) this->icon = ARROW_UP_FAR;
        else if (this->getPixel().y == this->previous->getPixel().y - 1) this->icon = ARROW_DOWN;
        else this->icon = ARROW_DOWN_FAR;
    }
    else if (this->getPixel().y == this->previous->getPixel().y) {
        if (this->getPixel().x == this->previous->getPixel().x + 1) this->icon = ARROW_LEFT;
        else if (this->getPixel().x > this->previous->getPixel().x + 1) this->icon = ARROW_LEFT_FAR;
        else if (this->getPixel().x == this->previous->getPixel().x - 1) this->icon = ARROW_RIGHT;
        else this->icon = ARROW_RIGHT_FAR;
    }
    else if (this->getPixel().x > this->previous->getPixel().x) {
        if (this->getPixel().y == this->previous->getPixel().y + 1) this->icon = ARROW_UPLEFT;
        else if (this->getPixel().y > this->previous->getPixel().y + 1) this->icon = ARROW_UPLEFT_FAR;
        else if (this->getPixel().y == this->previous->getPixel().y - 1) this->icon = ARROW_DOWNLEFT;
        else this->icon = ARROW_DOWNLEFT_FAR;
    }
    else if (this->getPixel().x < this->previous->getPixel().x) {
        if (this->getPixel().y == this->previous->getPixel().x + 1) this->icon = ARROW_UPRIGHT;
        else if (this->getPixel().y > this->previous->getPixel().x + 1) this->icon = ARROW_UPRIGHT_FAR;
        else if (this->getPixel().y == this->previous->getPixel().x - 1) this->icon = ARROW_DOWNRIGHT;
        else this->icon = ARROW_DOWNRIGHT_FAR;
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
