#include "particle.h"

#include "vector.h"

void phys::Particle::interact(Particle& p1, Particle& p2)
{
	Vector dist = p1.position_ - p2.position_;
	
	double mag = dist.magnitude();

	if (mag == 0) //dist of 0 would have no net direction, no net force
		return;

	dist /= mag;

	Vector force = dist * 6.67408e-11 * p1.mass_ * p2.mass_ / (mag * mag);

	force += dist * 8.987551787e9 * p1.charge_ * p2.charge_ / (mag * mag);

	double depth = p1.radius_ + p2.radius_ - mag;

	if(depth > 0)
	{
		force += dist * 1e6 * depth;
		force *= p1.hardness_ < p2.hardness_ ? p1.hardness_ : p2.hardness_;
	}

	p1.net_force_ += force;
	p2.net_force_ -= force;
}