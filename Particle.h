#pragma once
#include "Vec.h"

namespace phys
{
	class Particle
	{
	public:
		Particle(phys::Vector position, phys::Vector velocity, 
		double mass, double charge, double radius, double hardness) 
			: m_position{position}, m_velocity{velocity}, 
			m_acceleration{phys::Vector{0,0,0}}, 
			m_net_force{phys::Vector{0,0,0}}, m_mass{mass}, 
			m_charge{charge}, m_radius{radius}, m_hardness{hardness} {}

		phys::Vector Position() { return m_position; }
		void Add_Force(phys::Vector force) { m_net_force += force; }
		void Reset_Force() { m_net_force -= m_net_force; }
		void Update(double time) 
		{
			 m_acceleration = m_net_force / m_mass; 
			 m_velocity += m_acceleration * time; 
			 m_position += m_velocity * time; 
		}

		friend void Interact(Particle& p1, Particle& p2, double constant);
		friend void Collide(Particle& p1, Particle& p2);

	private:
		phys::Vector m_position;
		phys::Vector m_velocity;
		phys::Vector m_acceleration;
		phys::Vector m_net_force;
		double m_mass;
		double m_charge;
		double m_radius;
		double m_hardness;
	};

	void Interact(Particle& p1, Particle& p2, double constant);
	void Collide(Particle& p1, Particle& p2);
}