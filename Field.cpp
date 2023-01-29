#include "Field.h"

unsigned short Field::uncutGrassCounter = 0;

void Field::updateIcon()
{
    if (progress > 75) icon = GRASS_100_ICON;
    else if (progress > 50) icon = GRASS_75_ICON;
    else if (progress > 25) icon = GRASS_50_ICON;
    else if (progress > 0) icon = GRASS_25_ICON;
    else icon = GRASS_0_ICON;
}

Field::Field(const char& icon, const Pixel& pixel, const Pixel& margin) :
    Screen(pixel, margin)
{
    if (icon == MAP_GRASS_ICON) {
        uncutGrassCounter++;
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
    else grass = false;
    progress = 100;
}

Field::~Field()
{
}

bool Field::isGrass()
{
    return grass;
}

void Field::cutGrass(const float& amount)
{
    if (!grass || this->progress == 0) return;
    else {
        this->progress -= (short)ceil(amount * 100);
        if (this->progress == 0) Field::uncutGrassCounter--;
        updateIcon();
        draw();
    }
}
