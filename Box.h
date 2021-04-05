#pragma once

#include <SDL2/SDL.h>

#include "Point.h"

namespace phys
{
    struct Box
    {
        int x, y;
        int w, h;
        SDL_Rect Get_SDL_Rect() { return SDL_Rect{ x, y, w, h }; }
        bool Contains(Point& point)
        {
            if(point.x < x || point.y < y || point.x > x + w || point.x > y + h)
                return false;
            else return true;
        }
    };
}