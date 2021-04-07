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
				double c = 0, double r = 0, double h = 0)
			: position_{ p }, velocity_{ v }, mass_{ m }, charge_{ c }, radius_{ r }, 
				hardness_{ h }
			{}

		Particle() {}

		Vector position() 	{ return position_; }
		Vector velocity() 	{ return velocity_; }
		double mass() 		{ return mass_; }
		double charge() 	{ return charge_; }
		double radius() 	{ return radius_; }
		double hardness() 	{ return hardness_; }

		void set_position(const Vector& p) 	{ position_ = p; }
		void set_velocity(const Vector& v) 	{ velocity_ = v; }
		void set_mass(double m) 			{ mass_ = m; }
		void set_charge(double c) 			{ charge_ = c; }
		void set_radius(double r) 			{ radius_ = r; }
		void set_hardness(double h) 		{ hardness_ = h; }

		//Applies all forces and updates the position/velocity of both particles
		void update(double time)
		{
			acceleration_ 	= net_force_ / mass_;
			velocity_ 		+= acceleration_ * time;
			position_ 		+= velocity_ * time;
			net_force_ 		-= net_force_;
		}

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