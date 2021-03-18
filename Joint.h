#pragma once
#include "Vec.h"
#include "Particle.h"

typedef int ref_t;

namespace phys
{
    struct Joint
    {
        Joint(ref_t particle_1, ref_t particle_2, double tension, double length)
            : particle_1{ particle_1 }, particle_2{ particle_2 }, tension{ tension },
            length{ length } {}

        ref_t particle_1;
        ref_t particle_2;
        double tension;
        double length;

        void Apply(Particle* particles);
    };
}