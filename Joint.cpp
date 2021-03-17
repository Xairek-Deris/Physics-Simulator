#include "Joint.h"

void phys::Joint::Apply()
{
	phys::Vector vec = particle_1->position - particle_2->position;
	double mag = vec.Magnitude();
	vec /= mag;
	vec *= (length - mag) * tension;
	particle_1->Add_Force(vec);
	particle_2->Add_Force(-vec);
}