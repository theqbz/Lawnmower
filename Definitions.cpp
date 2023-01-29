#include "Definitions.h"

Pixel Pixel::operator+(const Pixel& right) const
{
    Pixel pixel{ 0,0 };
    pixel.y = this->y + right.y;
    pixel.x = this->x + right.x;
    return pixel;
}
