#include "Field.h"

void phys::Interact(Field& f1, Field& f2, double constant)
{
	phys::Vector vec = f1.kinetic.position - f2.kinetic.position;			//distance between the vectors
	double mag = vec.Magnitude();										//distance squared
	if (mag == 0)														//distance of 0 would have no net direction, so no net force
		return;
	vec /= mag;													//normalized distance vector	
	vec *= constant * f1.magnitude * f2.magnitude / (mag * mag);
	f1.kinetic.Add_Force(vec);
	f2.kinetic.Add_Force(-vec);												//equal and opposite and all that jazz
}