#pragma once
#include "Screen.h"

class Field :
    public Screen
{
    bool  grass;
    bool  available;
    short progress;
    void updateIcon();
public:
    static short uncutGrassCounter;
    Field(const char&, const Pixel&, const Pixel&);
    ~Field();
    bool isAwailable();
    void cutGrass(const float&);
};

