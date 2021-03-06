#include <iostream>
#include "vector3.h"
#include "vector4.h"

Vector3 Vector3::Zero = Vector3(0.f, 0.f, 0.f);
Vector4 Vector4::Zero = Vector4(0.f, 0.f, 0.f, 0.f);

std::ostream & operator<<(std::ostream & o, const Vector3 & rhs)
{
	return o << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
}

std::ostream & operator<<(std::ostream & o, const Vector4 & rhs)
{
	return o << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")";
}

