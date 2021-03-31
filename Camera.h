#pragma once

#include "Vec.h"

namespace phys
{
    struct Mouse
    {
        int x, y;
    };

    struct Camera
    {
        Camera(const Vector& pos, const Vector& vel, double zoo) : position{ pos }, velocity{ vel }, zoom{ zoo } {}
        Camera() : position{ Vector{ 0, 0, 0 } }, velocity{ Vector{ 0, 0, 0} }, zoom{ 100 } {}
        
        Vector position;
        Vector velocity;
        Mouse mouse;
        double zoom;

        void Update(double time) { position += velocity * time; }
    };
}