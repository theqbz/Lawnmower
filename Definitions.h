#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>
#include <thread>

typedef std::vector<std::string> vString;

struct Location
{
    float y, x;
};

struct Pixel
{
    short y, x;
    Pixel& operator=(const Pixel&);
    Pixel operator+(const Pixel&) const;
    void reciveLocation(const Location&);
};

struct Colors
{
    short text, background;
};

#define PI                      3.14159265359f
#define LAWNMOWER_ICON          char(219)
#define LAWNMOWER_COLOR         Colors{4,0}
#define LAWNMOWER_LOW_BATTERY   30
#define DOCK_ICON               char(4)
#define DOCK_COLOR              Colors{4,2}
#define GRASS_NEW_ICON          char(219)
#define GRASS_100_ICON          char(178)
#define GRASS_75_ICON           char(177)
#define GRASS_50_ICON           char(176)
#define GRASS_25_ICON           char(241)
#define GRASS_0_ICON            char(32)
#define GRASS_COLOR             Colors{10,0}
#define BARRIER_ICON            char(88)
#define BARRIER_COLOR           Colors{14,2}
#define TREE_ICON               char(5)
#define TREE_COLOR              Colors{6,2}
#define UNDEF_ICON              char(32)
#define UNDEF_COLOR             Colors{0,0}
#define MAP_GRASS_ICON          '.'
#define MAP_BARRIER_ICON        'w'
#define MAP_TREE_ICON           't'
#define MAP_DOCK_ICON           'd'
#define MAP_UNDEFINED_ICON      '-'

