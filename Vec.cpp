#include "Vec.h"

phys::Vector phys::Vector::operator*=(const Vector& vec)
{
	Vector temp = *this;
	x = temp.y * vec.z - temp.z * vec.y;
	y = temp.z * vec.x - temp.x * vec.z;
	z = temp.x * vec.y - temp.y * vec.x;
	return *this;
}