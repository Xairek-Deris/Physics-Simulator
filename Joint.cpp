#include "Joint.h"

void phys::Joint::Apply()
{
	phys::Vector vec = kinetic_1.position - kinetic_2.position;
	double mag = vec.Magnitude();
	vec /= mag;
	vec *= (length - mag) * tension;
	kinetic_1.Add_Force(vec);
	kinetic_2.Add_Force(-vec);
}
