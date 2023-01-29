#include "Field.h"

short Field::count = 0;

Field::Field(const char& icon, const Pixel& pixel) :
    Screen(pixel)
{
    if (icon == MAP_GRASS_ICON) {
        grass = true;
        this->icon = GRASS_100_ICON;
        this->colors = GRASS_COLOR;
    }
    else if (icon == MAP_BARRIER_ICON) {
        grass = false;
        this->icon = BARRIER_ICON;
        this->colors = BARRIER_COLOR;
    }
    else if (icon == MAP_TREE_ICON) {
        grass = false;
        this->icon = TREE_ICON;
        this->colors = TREE_COLOR;
    }
    progress = 100;
    count++;
}

Field::~Field()
{
    count--;
}
