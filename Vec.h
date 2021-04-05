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
		Vector operator*= (const Vector& vec);
		double Dot(const Vector& v) const { return x * v.x + y * v.y + z * v.z; }
		double Mag_Squared() const { return x * x + y * y + z * z; }
		double Magnitude() const { return sqrt(this->Mag_Squared()); }
		Vector Normalize() { *this /= this->Magnitude(); return *this; }
		Vector operator- () const { return Vector{ -x, -y, -z }; }
	};

	Vector operator+ (const Vector& v1, const Vector& v2);
	Vector operator- (const Vector& v1, const Vector& v2);
	Vector operator* (const Vector& v, const double d);
	Vector operator/ (const Vector& v, const double d);
	Vector operator* (const Vector& v1, const Vector& v2);
	bool operator== (const Vector& v1, const Vector& v2);
	bool operator!= (const Vector& v1, const Vector& v2);
}