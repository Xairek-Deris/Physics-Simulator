#pragma once

#include <SDL2/SDL.h>

namespace phys
{
    class Point
    {
    public:
        Point(int x, int y) : m_point{ x, y } {}
        Point() : m_point{ 0, 0 } {}

        const SDL_Point* Get_Point() const { return &m_point; }
        int X() { return m_point.x; }
        int Y() { return m_point.y; }
        void Set_X(int x) { m_point.x = x; }
        void Set_Y(int y) { m_point.y = y; }
        Point operator+=(Point& point) { m_point.x += point.m_point.x; m_point.y += point.m_point.y; return *this; }
        Point operator-=(Point& point) { m_point.x -= point.m_point.x; m_point.y -= point.m_point.y; return *this; }
    private:
        SDL_Point m_point;
    };

    inline Point operator+(Point& p1, Point& p2) { Point ret = p1; return ret += p2; }
    inline Point operator-(Point& p1, Point& p2) { Point ret = p1; return ret -= p2; }
}