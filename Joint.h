#pragma once
#include "Vec.h"
#include "Particle.h"

namespace phys
{
    struct Joint
    {
        Joint(phys::Particle* particle_1, phys::Particle* particle_2, double tension, double length)
            : particle_1{ particle_1 }, particle_2{ particle_2 }, tension{ tension }, length{ length } {}

        phys::Particle* particle_1;
        phys::Particle* particle_2;
        double tension;
        double length;

        void Apply();
    };
}