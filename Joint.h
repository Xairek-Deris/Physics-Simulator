#pragma once
#include "Kinetic.h"
#include "Vec.h"

namespace phys
{
	struct Joint
	{
		Joint(double ten, double len, phys::Kinetic& k_1, phys::Kinetic& k_2) : tension{ ten }, length{ len }, kinetic_1{ k_1 }, kinetic_2{ k_2 } {}

		double tension;
		double length;
		phys::Kinetic& kinetic_1;
		phys::Kinetic& kinetic_2;

		void Apply();
	};
}