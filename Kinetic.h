#pragma once
#include "Vec.h"

namespace phys
{
	struct Kinetic
	{
		Kinetic(double mas, phys::Vector& pos, phys::Vector& vel)
			:mass{ mas }, position{ pos }, velocity{ vel }, 
			acceleration{ phys::Vector{0,0,0} }, net_force{ phys::Vector{0,0,0} } {}

		double mass;
		phys::Vector position;
		phys::Vector velocity;
		phys::Vector acceleration;
		phys::Vector net_force;

		void Add_Force(phys::Vector force) { net_force += force; }
		void Reset_Force() { net_force -= net_force; }
		void Update(double time) { acceleration = net_force / mass; velocity += acceleration * time; position += velocity * time; }
	};
}