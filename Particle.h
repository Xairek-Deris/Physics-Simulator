#pragma once
#include "Vec.h"

namespace phys
{
	struct Particle
	{
		phys::Vector position;
		phys::Vector velocity;
		phys::Vector acceleration;
		phys::Vector net_force;
		double mass;
		double charge;
		double radius;
		double hardness;
		
		void Add_Force(phys::Vector force) { net_force += force; }
		void Reset_Force() { net_force -= net_force; }
		void Update(double time) { acceleration = net_force / mass; velocity += acceleration * time; position += velocity * time; }
	};

	void Elec_Interact(Particle& p1, Particle& p2);
	void Grav_Interact(Particle& p1, Particle& p2);
	void Collide(Particle& p1, Particle& p2);
}