#pragma once
#include "Kinetic.h"
#include "Vec.h"

namespace phys
{
	struct Collider
	{
		Collider(double rad, double har, phys::Kinetic& kin) : radius{ rad }, hardness{ har }, kinetic{ kin }{}

		double radius;
		double hardness;
		phys::Kinetic& kinetic;
	};

	void Collide(Collider& c1, Collider& c2);
}