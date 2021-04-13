#pragma once

#include <SDL2/SDL.h>

#include "point.h"

namespace disp
{
    //wrapper for SDL rect that works for drawing. Safe to move or copy.
    class Box
    {
    public:

        Box(int x = 0, int y = 0, int w = 0, int h = 0) 
        : box_{ x, y, w, h } 
        {}

        int& x()        { return box_.x; }
        int& y()        { return box_.y; }
        int& width()    { return box_.w; }
        int& height()   { return box_.h; }

        const SDL_Rect* rect() const { return &box_; }

        bool contains_point(const Point& p) const
        {
            return SDL_PointInRect(p.point(), &box_);
        }

    private:
        SDL_Rect box_;
    };
} //namespace disp