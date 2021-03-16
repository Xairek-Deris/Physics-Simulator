#pragma once
#include "Kinetic.h"
#include "Vec.h"

namespace phys
{
	struct Field
	{
		Field(double mag, phys::Kinetic& kin)
			:magnitude{ mag }, kinetic{ kin } {}

		double magnitude;
		phys::Kinetic& kinetic;
	};

	//adds forces between the two fields to their net_force member
	void Interact(Field& f1, Field& f2, double constant);
}