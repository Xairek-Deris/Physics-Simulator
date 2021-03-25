#pragma once

#include <vector>

#include "Vec.h"

namespace phys
{
	struct Particle
	{
	public:
		Particle(phys::Vector position, phys::Vector velocity,
		double mass, double charge, double radius, double hardness)
			: position{ position }, velocity{ velocity },
			acceleration{ phys::Vector{ 0,0,0 } },
			net_force{ phys::Vector{ 0,0,0 } }, mass{mass},
			charge{ charge }, radius{ radius }, hardness{ hardness } {}
		phys::Vector position;
		phys::Vector velocity;
		phys::Vector acceleration;
		phys::Vector net_force;
		double mass;
		double charge;
		double radius;
		double hardness;
		static void Electrify(Particle& p1, Particle& p2);
		static void Gravitate(Particle& p1, Particle& p2);
		static void Collide(Particle& p1, Particle& p2);
		void Update(double time)
		{
			acceleration = net_force / mass;
			velocity += acceleration * time;
			position += velocity * time;
			net_force -= net_force;
		}
	};
}