#pragma once
#include <math.h>

namespace phys
{
	struct Vector
	{
		double x;
		double y;
		double z;

		//addition
		Vector operator+= (const Vector& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector operator+ (const Vector& v) const { Vector ret = *this; return ret += v; }

		//subtraction
		Vector operator-= (const Vector& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vector operator- (const Vector& v) const { Vector ret = *this; return ret -= v; }

		//multiplication by a scalar
		Vector operator*= (const double d) { x *= d; y *= d; z *= d; return *this; }
		Vector operator* (const double d) const { Vector ret = *this; return ret *= d; }

		//division by a scalar
		Vector operator/= (const double d) { x /= d; y /= d; z /= d; return *this; }
		Vector operator/ (const double d) const { Vector ret = *this; return ret /= d; }

		//cross product multiplication
		Vector operator*= (const Vector& vec);
		Vector operator* (const Vector& vec) const { Vector ret = *this; return ret *= vec; }

		//dot product
		double Dot(const Vector& v) const { return x * v.x + y * v.y + z * v.z; }

		//magnitude of the vector squared
		double Mag_Squared() const { return x * x + y * y + z * z; }

		//magnitude of the vector
		double Magnitude() const { return sqrt(this->Mag_Squared()); }

		//Normalize vector into unit vector
		void Normalize() { *this /= this->Magnitude(); }

		//negation
		Vector operator- () const { return Vector{ -x, -y, -z }; }
		
		//relational operators
		bool operator== (const Vector& v) const { return x == v.x && y == v.y && z == v.z; }
		bool operator!= (const Vector& v) const { return !(x == v.x && y == v.y && z == v.z); }
		bool operator> (const Vector& v) const { return Mag_Squared() > v.Mag_Squared(); }
		bool operator< (const Vector& v) const { return Mag_Squared() < v.Mag_Squared(); }
		bool operator>= (const Vector& v) const { return Mag_Squared() >= v.Mag_Squared(); }
		bool operator<= (const Vector& v) const { return Mag_Squared() <= v.Mag_Squared(); }
	};
}