#include "Lawnmower.h"

Lawnmower::Lawnmower(const Pixel& pixel) :
    Screen(LAWNMOWER_ICON, pixel, LAWNMOWER_COLOR)
{
    location.x = (float)pixel.x + 0.5f;
    location.y = (float)pixel.y + 0.5f;
    heading = PI / 2.0f;
    battery = 100;
    dock = pixel;
}
