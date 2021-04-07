#pragma once

#include <math.h>

namespace phys
{
	//3d vector with mathematics capability. Safe to move and copy.
	class Vector
	{
	public:
		Vector(double x = 0, double y = 0, double z = 0) 
		: x_{ x }, y_{ y }, z_{ z }
		{}

		double x() const { return x_; }
		double y() const { return y_; }
		double z() const { return z_; }

		//Returns the vector's magnitude squared (without using sqrt())
		double mag_squared() const 
		{
			return x_ * x_ + y_ * y_ + z_ * z_;
		}

		//Returns the vector magnitude
		double magnitude() const
		{
			return sqrt(this->mag_squared());
		}

		//Returns the dot product
		double dot(const Vector& v) const
		{
			return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
		}

		Vector operator+= (const Vector& v)
		{
			x_ += v.x_;
			y_ += v.y_;
			z_ += v.z_;
			return *this;
		}

		Vector operator-= (const Vector& v)
		{
			x_ -= v.x_;
			y_ -= v.y_;
			z_ -= v.z_;
			return *this;
		}

		//Multplication by a scalar
		Vector operator*= (const double d)
		{
			x_ *= d;
			y_ *= d;
			z_ *= d;
			return *this;
		}

		//Division by a scalar
		Vector operator/= (const double d)
		{
			x_ /= d;
			y_ /= d;
			z_ /= d;
			return *this;
		}

		//Vector cross product
		Vector operator*= (const Vector& vec)
		{
			Vector temp = *this;
			x_ = temp.y_ * vec.z_ - temp.z_ * vec.y_;
			y_ = temp.z_ * vec.x_ - temp.x_ * vec.z_;
			z_ = temp.x_ * vec.y_ - temp.y_ * vec.x_;
			return *this;
		}

		Vector normalize()
		{
			*this /= this->magnitude();
			return *this;
		}

		Vector operator- () const 
		{
			return Vector{ -x_, -y_, -z_ };
		}

	private:
		double x_;
		double y_;
		double z_;
	};

	inline Vector operator+ (const Vector& v1, const Vector& v2)
	{
		Vector ret = v1; return ret += v2;
	}

	inline Vector operator- (const Vector& v1, const Vector& v2)
	{
		Vector ret = v1;
		return ret -= v2;
	}

	//Multplication by a scalar
	inline Vector operator* (const Vector& v, const double d)
	{
		Vector ret = v;
		return ret *= d;
	}

	//Division by a scalar
	inline Vector operator/ (const Vector& v, const double d)
	{
		Vector ret = v;
		return ret /= d;
	}

	//Vector cross product
	inline Vector operator* (const Vector& v1, const Vector& v2)
	{
		Vector ret = v1;
		return ret *= v2;
	}

	inline bool operator== (const Vector& v1, const Vector& v2)  
	{
		return v1.x() == v2.x() && v1.y() == v2.y() && v1.z() == v2.z();
	}

	inline bool operator!= (const Vector& v1, const Vector& v2)  
	{
		return !(v1.x() == v2.x() && v1.y() == v2.y() && v1.z() == v2.z());
	}

} //namespace phys