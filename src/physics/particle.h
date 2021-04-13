#pragma once

#include "vector.h"

namespace phys
{
	//Particles with the standard physical properties.
	//Designed to interact with each other. All values are in SI units
	//except hardness which would be mega-newtons per meter of penetration
	//Safe to move or copy.
	class Particle
	{
	public:
		//p = position, v = velocity, m = mass, c = charge, r = radius, h = hardness
		Particle(const Vector& p = {}, const Vector& v = {}, double m = 1, 
				double c = 0, double r = 0, double h = 0);

		Vector& position() 	{ return position_; }
		Vector& velocity() 	{ return velocity_; }
		double& mass() 		{ return mass_; }
		double& charge() 	{ return charge_; }
		double& radius() 	{ return radius_; }
		double& hardness() 	{ return hardness_; }

		//Applies all forces and updates the position/velocity of both particles
		void update(double time);

		static void interact(Particle& p1, Particle& p2);

	private:
		double mass_;
		double charge_;
		double radius_;
		double hardness_;

		Vector position_;
		Vector velocity_;
		Vector acceleration_;
		Vector net_force_;
	};
} //namespace phys