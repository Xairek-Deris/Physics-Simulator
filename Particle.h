#pragma once

#include <vector>

#include "Vec.h"

namespace phys
{
	struct Particle
	{
		Particle(const Vector& pos, const Vector& vel, double mas, double cha, double rad, double har)
			: position{ pos }, velocity{ vel }, acceleration{ Vector{ 0,0,0 } }, net_force{ Vector{ 0,0,0 } }, mass{mas}, charge{ cha }, radius{ rad }, hardness{ har } {}

		Vector position;
		Vector velocity;
		Vector acceleration;
		Vector net_force;
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