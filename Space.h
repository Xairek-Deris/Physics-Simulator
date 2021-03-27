#pragma once

#include <string>
#include <vector>

#include "Particle.h"

namespace phys
{
    struct Space
    {
        int Load(const std::string& filename);
        int Save(const std::string& filename);
        void Update(double time);

        std::vector<Particle> particles;
        std::vector<Particle> obstacles;
    };
}