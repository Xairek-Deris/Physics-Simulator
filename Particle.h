#pragma once

#include <SDL2/SDL.h>

#include "Vec.h"

namespace phys
{
	struct Particle
	{
		Particle(const Vector& pos, const Vector& vel, double mas, double cha, double rad, double har, SDL_Texture* tex)
			: position{ pos }, velocity{ vel }, acceleration{ Vector{ 0,0,0 } }, net_force{ Vector{ 0,0,0 } }, mass{mas}, charge{ cha }, radius{ rad }, hardness{ har }, texture{ tex } {}

		Vector position;
		Vector velocity;
		Vector acceleration;
		Vector net_force;
		double mass;
		double charge;
		double radius;
		double hardness;
		SDL_Texture* texture;

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