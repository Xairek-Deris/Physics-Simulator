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
		Vector operator+= (const Vector& vec) { x += vec.x; y += vec.y; z += vec.z; return *this; }
		Vector operator+ (const Vector& vec) const { Vector ret = *this; return ret += vec; }

		//subtraction
		Vector operator-= (const Vector& vec) { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
		Vector operator- (const Vector& vec) const { Vector ret = *this; return ret -= vec; }

		//multiplication by a scalar
		Vector operator*= (const double mult) { x *= mult; y *= mult; z *= mult; return *this; }
		Vector operator* (const double mult) const { Vector ret = *this; return ret *= mult; }

		//division by a scalar
		Vector operator/= (const double div) { x /= div; y /= div; z /= div; return *this; }
		Vector operator/ (const double div) const { Vector ret = *this; return ret /= div; }

		//cross product multiplication
		Vector operator*= (const Vector& vec);
		Vector operator* (const Vector& vec) const { Vector ret = *this; return ret *= vec; }

		//dot product
		double Dot(const Vector& vec) { return x * vec.x + y * vec.y + z * vec.z; }

		//magnitude of the vector squared
		double Mag_Squared() { return x * x + y * y + z * z; }

		//magnitude of the vector
		double Magnitude() { return sqrt(this->Mag_Squared()); }

		//Normalize vector into unit vector
		void Normalize() { *this /= this->Magnitude(); }

		//negation
		Vector operator- () { return Vector{ -x, -y, -z }; }
	};
} 