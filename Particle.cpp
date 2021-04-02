#include "Particle.h"

#include "Vec.h"

void phys::Particle::Interact(Particle& p1, Particle& p2)
{
	Vector dist = p1.position - p2.position;
	double mag = dist.Magnitude();
	if (mag == 0)															//distance of 0 would have no net direction, so no net force
		return;
	dist /= mag;															//normalized distance vector
	Vector force = dist * 6.67408e-11 * p1.mass * p2.mass / (mag * mag);
	force += dist * 8.987551787e9 * p1.charge * p2.charge / (mag * mag);		//Coulomb's constant
	double depth = p1.radius + p2.radius - mag;
	if(depth > 0)
	{
		force += dist * 1e6 * depth * (p1.hardness < p2.hardness ? p1.hardness : p2.hardness);
	}
	p1.net_force += force;
	p2.net_force -= force;
}