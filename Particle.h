#pragma once

#include "Vec.h"

namespace phys
{
	struct Particle
	{
		Particle(const Vector& pos, const Vector& vel, double mas, double cha, double rad, double har, unsigned tex)
			: position{ pos }, velocity{ vel }, acceleration{ Vector{ 0,0,0 } }, net_force{ Vector{ 0,0,0 } }, mass{mas}, charge{ cha }, radius{ rad }, hardness{ har }, texture{ tex } {}
		Particle() 
			: position{ Vector{ 0, 0, 0 } }, velocity{ Vector{ 0, 0, 0 } }, acceleration{ Vector{ 0,0,0 } }, net_force{ Vector{ 0,0,0 } }, mass{ 0 }, charge{ 0 }, radius{ 0 }, hardness{ 0 }, texture{ 0 } {}

		Vector position;
		Vector velocity;
		Vector acceleration;
		Vector net_force;
		double mass;
		double charge;
		double radius;
		double hardness;
		unsigned texture;

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