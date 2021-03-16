#include "Particle.h"

void phys::Interact(phys::Particle& p1, phys::Particle& p2, double constant)
{
	phys::Vector vec = p1.m_position - p2.m_position;
	double mag = vec.Magnitude();
	if (mag == 0)													//distance of 0 would have no net direction, so no net force
		return;
	vec /= mag;														//normalized distance vector	
	vec *= constant * p1.m_charge * p2.m_charge / (mag * mag);		//Coulomb's constant
	p1.Add_Force(vec);
	p2.Add_Force(-vec);
}

void phys::Collide(Particle& p1, Particle& p2)
{
		phys::Vector vec = p1.m_position - p2.m_position;
	double mag = vec.Magnitude();
	if (mag == 0)													//distance of zero would have no net force
		return;
	double depth = p1.m_radius + p2.m_radius;
	depth -= mag;													//penetration depth
	if (depth > 0)
	{
		vec /= mag;													//normalize dist vector
		vec *= depth * (p1.m_hardness < p2.m_hardness ?
			p1.m_hardness : p2.m_hardness);	 						//force calculated using the softer object
		p1.Add_Force(vec);
		p2.Add_Force(-vec);
	}
}