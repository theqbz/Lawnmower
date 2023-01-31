#include "Definitions.h"

Pixel& Pixel::operator=(const Pixel& right)
{
    if (this == &right) return *this;
    this->y = right.y;
    this->x = right.x;
    return *this;
}

Pixel Pixel::operator+(const Pixel& right) const
{
    Pixel pixel{ 0,0 };
    pixel.y = this->y + right.y;
    pixel.x = this->x + right.x;
    return pixel;
}

Pixel& Pixel::operator--()
{
    this->y--;
    this->x--;
    return *this;
}

bool Pixel::operator==(const Pixel& right) const
{
    return this->x == right.x && this->y == right.y;
}

void Pixel::reciveLocation(const Location& location)
{
    this->y = (short)location.y;
    this->x = (short)location.x;
}
