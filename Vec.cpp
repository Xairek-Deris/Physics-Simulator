#include "Vec.h"

phys::Vector phys::Vector::operator*=(const Vector& vec)
{
	Vector temp = *this;
	x = temp.y * vec.z - temp.z * vec.y;
	y = temp.z * vec.x - temp.x * vec.z;
	z = temp.x * vec.y - temp.y * vec.x;
	return *this;
}

phys::Vector phys::operator+ (const Vector& v1, const Vector& v2) { Vector ret = v1; return ret += v2; }
phys::Vector phys::operator- (const Vector& v1, const Vector& v2) { Vector ret = v1; return ret -= v2; }
phys::Vector phys::operator* (const Vector& v, const double d)    { Vector ret = v; return ret *= d; }
phys::Vector phys::operator/ (const Vector& v, const double d)    { Vector ret = v; return ret /= d; }
phys::Vector phys::operator* (const Vector& v1, const Vector& v2) { Vector ret = v1; return ret *= v2; }
bool phys::operator== (const Vector& v1, const Vector& v2)  { return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z; }
bool phys::operator!= (const Vector& v1, const Vector& v2)  { return !(v1.x == v2.x && v1.y == v2.y && v1.z == v2.z); }