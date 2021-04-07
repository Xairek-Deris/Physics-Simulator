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
        
        int x() const           { return box_.x; }
        int y() const           { return box_.y; }
        int width() const       { return box_.w; }
        int height() const      { return box_.h; }
        void set_x(int x)       { box_.x = x; }
        void set_y(int y)       { box_.y = y; }
        void set_width(int w)   { box_.w = w; }
        void set_height(int h)  { box_.h = h; }

        const SDL_Rect* rect() const { return &box_; }

        bool contains_point(const Point& p) const
        {
            return SDL_PointInRect(p.point(), &box_);
        }

    private:
        SDL_Rect box_;
    };
} //namespace disp