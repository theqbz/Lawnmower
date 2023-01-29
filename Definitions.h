#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Pixel
{
    short x, y;
};

struct Location
{
    float x, y;
};

struct Colors
{
    short text, background;
};

#define PI                  3.14159f
#define LAWNMOWER_ICON      char(219)
#define LAWNMOWER_COLOR     Colors{4,0}
#define GRASS_100_ICON      char(219)
#define GRASS_75_ICON       char(178)
#define GRASS_50_ICON       char(177)
#define GRASS_25_ICON       char(176)
#define GRASS_0_ICON        char(32)
#define GRASS_COLOR         Colors{2,10}
#define BARRIER_ICON        char(88)
#define BARRIER_COLOR       Colors{14,2}
#define MAP_GRASS_ICON      '.'
#define MAP_BARRIER_ICON    'w'

