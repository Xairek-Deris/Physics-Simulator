#pragma once

#include <SDL2/SDL.h>

namespace disp
{
    //wrapper for SDL_point. Safe to move or copy.
    class Point
    {
    public:
        Point(int x = 0, int y = 0)
        : point_{ x, y }
        {}

        int x()             { return point_.x; }
        int y()             { return point_.y; }
        void set_x(int x)   { point_.x = x; }
        void set_y(int y)   { point_.y = y; }

        const SDL_Point* point() const { return &point_; }

        Point operator+=(Point& point) { point_.x += point.point_.x; point_.y += point.point_.y; return *this; }
        Point operator-=(Point& point) { point_.x -= point.point_.x; point_.y -= point.point_.y; return *this; }
        
    private:
        SDL_Point point_;
    };

    inline Point operator+(Point& p1, Point& p2) { Point ret = p1; return ret += p2; }
    inline Point operator-(Point& p1, Point& p2) { Point ret = p1; return ret -= p2; }
} //namespace disp