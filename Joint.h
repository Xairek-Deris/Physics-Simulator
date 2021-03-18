#pragma once
#include "Vec.h"
#include "Particle.h"

namespace phys
{
    struct Joint
    {
        Joint(size_t particle_1, size_t particle_2, double tension, double length)
            : particle_1{ particle_1 }, particle_2{ particle_2 }, tension{ tension },
            length{ length } {}

        size_t particle_1;
        size_t particle_2;
        double tension;
        double length;

        void Apply(Particle* particles);
    };
}