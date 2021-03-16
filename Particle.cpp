#include "Particle.h"

void phys::Elec_Interact(phys::Particle& p1, phys::Particle& p2)
{
	phys::Vector vec = p1.position - p2.position;
	double mag = vec.Magnitude();
	if (mag == 0)													//distance of 0 would have no net direction, so no net force
		return;
	vec /= mag;														//normalized distance vector	
	vec *= 8.987551787e9 * p1.charge * p2.charge / (mag * mag);		//Coulomb's constant
	p1.Add_Force(vec);
	p2.Add_Force(-vec);
}

void phys::Grav_Interact(Particle& p1, Particle& p2)
{
		phys::Vector vec = p1.position - p2.position;
	double mag = vec.Magnitude();
	if (mag == 0)													//distance of 0 would have no net direction, so no net force
		return;
	vec /= mag;														//normalized distance vector	
	vec *= 6.67408e-11 * p1.charge * p2.charge / (mag * mag);		//Coulomb's constant
	p1.Add_Force(vec);
	p2.Add_Force(-vec);
}

void phys::Collide(Particle& p1, Particle& p2)
{
		phys::Vector vec = p1.position - p2.position;
	double mag = vec.Magnitude();
	if (mag == 0)													//distance of zero would have no net force
		return;
	double depth = p1.radius + p2.radius;
	depth -= mag;													//penetration depth
	if (depth > 0)
	{
		vec /= mag;													//normalize dist vector
		vec *= depth * (p1.hardness < p2.hardness ? p1.hardness : p2.hardness);	 //force calculated using the softest object
		p1.Add_Force(vec);
		p2.Add_Force(-vec);
	}
}