#include <iostream>
#include "quaternion.h"

Quaternion Quaternion::Zero = Quaternion(Vector3::Zero, 0.f);

std::ostream & operator<<(std::ostream & o, const Quaternion & rhs)
{
	return o << "[" << rhs.u << " + " << rhs.w << "]";
}
