#pragma once

#include <SDL2/SDL.h>

#include "Point.h"

namespace phys
{
    class Box
    {
    public:
        Box(int x, int y, int w, int h) : m_box{ x, y, w, h } {}
        Box() : m_box{ 0, 0, 0, 0 } {}
        
        const SDL_Rect* Get_Rect() const { return &m_box; }
        int X() const { return m_box.x; }
        int Y() const { return m_box.y; }
        int Width() const { return m_box.w; }
        int Height() const { return m_box.h; }
        void Set_X(int x) { m_box.x = x; }
        void Set_Y(int y) { m_box.y = y; }
        void Set_Width(int w) { m_box.w = w; }
        void Set_Height(int h) { m_box.h = h; }
        bool Contains(const Point& point) const
        {
            return SDL_PointInRect(point.Get_Point(), &m_box);
        }
    private:
        SDL_Rect m_box;
    };
}