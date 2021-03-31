#pragma once

#include <vector>

#include "Camera.h"
#include "Particle.h"

namespace phys
{
    struct Space
    {
        void Update(double time);

        std::vector<Particle> particles;
        std::vector<Particle> obstacles;
        std::vector<Camera> cameras;
    };
}