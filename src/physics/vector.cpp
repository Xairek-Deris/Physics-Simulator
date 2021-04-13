#include "vector.h"

phys::Vector phys::Vector::operator*= (const Vector& vec)
{
    Vector temp = *this;
    x_ = temp.y_ * vec.z_ - temp.z_ * vec.y_;
    y_ = temp.z_ * vec.x_ - temp.x_ * vec.z_;
    z_ = temp.x_ * vec.y_ - temp.y_ * vec.x_;
    return *this;
}