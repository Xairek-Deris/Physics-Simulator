#pragma once

#include <SDL2/SDL.h>

namespace phys
{
    struct Point
    {
        int x, y;
        Point operator+=(Point& point) { x += point.x; y += point.y; return *this; }
        Point operator-=(Point& point) { x -= point.x; y -= point.y; return *this; }
        SDL_Point Get_SDL_Point() { return SDL_Point{ x, y }; }
    };

    inline Point operator+(Point& p1, Point& p2) { Point ret = p1; return ret += p2; }
    inline Point operator-(Point& p1, Point& p2) { Point ret = p1; return ret -= p2; }
}