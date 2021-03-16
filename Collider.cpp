#include "Collider.h"

void phys::Collide(Collider& c1, Collider& c2)
{
	phys::Vector vec = c1.kinetic.position - c2.kinetic.position;
	double mag = vec.Magnitude();
	if (mag == 0)													//distance of zero would have no net force
		return;
	double depth = c1.radius + c2.radius;
	depth -= mag;													//penetration depth
	if (depth > 0)
	{
		vec /= mag;													//normalize dist vector
		vec *= depth * (c1.hardness < c2.hardness ? c1.hardness : c2.hardness);	 //force calculated using the softest object
		c1.kinetic.Add_Force(vec);
		c2.kinetic.Add_Force(-vec);
	}
}