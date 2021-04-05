#pragma once

#include <math.h>

namespace phys
{
	struct Vector
	{
		double x;
		double y;
		double z;

		Vector operator+= (const Vector& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector operator-= (const Vector& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vector operator*= (const double d) { x *= d; y *= d; z *= d; return *this; }
		Vector operator/= (const double d) { x /= d; y /= d; z /= d; return *this; }
		Vector operator*= (const Vector& vec)
		{
			Vector temp = *this;
			x = temp.y * vec.z - temp.z * vec.y;
			y = temp.z * vec.x - temp.x * vec.z;
			z = temp.x * vec.y - temp.y * vec.x;
			return *this;
		}
		double Dot(const Vector& v) const { return x * v.x + y * v.y + z * v.z; }
		double Mag_Squared() const { return x * x + y * y + z * z; }
		double Magnitude() const { return sqrt(this->Mag_Squared()); }
		Vector Normalize() { *this /= this->Magnitude(); return *this; }
		Vector operator- () const { return Vector{ -x, -y, -z }; }
	};

	inline Vector operator+ (const Vector& v1, const Vector& v2) { Vector ret = v1; return ret += v2; }
	inline Vector operator- (const Vector& v1, const Vector& v2) { Vector ret = v1; return ret -= v2; }
	inline Vector operator* (const Vector& v, const double d)    { Vector ret = v; return ret *= d; }
	inline Vector operator/ (const Vector& v, const double d)    { Vector ret = v; return ret /= d; }
	inline Vector operator* (const Vector& v1, const Vector& v2) { Vector ret = v1; return ret *= v2; }
	inline bool operator== (const Vector& v1, const Vector& v2)  { return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z; }
	inline bool operator!= (const Vector& v1, const Vector& v2)  { return !(v1.x == v2.x && v1.y == v2.y && v1.z == v2.z); }
}