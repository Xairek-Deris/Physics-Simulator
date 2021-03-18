#include "Joint.h"

void phys::Joint::Apply(Particle* particles)
{
	phys::Vector vec = (particles + particle_1)->position - (particles + particle_2)->position;
	double mag = vec.Magnitude();
	vec /= mag;
	vec *= (length - mag) * tension;
	(particles + particle_1)->Add_Force(vec);
	(particles + particle_2)->Add_Force(-vec);
}