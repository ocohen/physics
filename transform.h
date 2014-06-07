#ifndef OC_TRANSFORM_H
#define OC_TRANSFORM_H

#include <iostream>
#include "vector3.h"
#include "quaternion.h"

struct Transform
{
	Vector3 pos;
	Quaternion	rot;
	Vector3 scale;

	Transform(const Vector3 & inTranslation = Vector3::Zero, const Quaternion &  inRotation = Quaternion::Zero, const Vector3 & inScale = Vector3(1,1,1)) :
	pos(inTranslation), rot(inRotation), scale(inScale){}
	
	Vector3 TransformPosition(const Vector3 & v) const
	{
		return rot.Rotate(v * scale) + pos;
	}
	
	Vector3 TransformVector(const Vector3 & v) const
	{
		return rot.Rotate(v*scale);
	}
	
	Vector3 TransformPositionNoScale(const Vector3 & v) const
	{
		return rot.Rotate(v) + pos;
	}
	
	//we use normal math style. So in this case A.Concat(B) = AB like a regular math textbook
	Transform Concat(const Transform & rhs) const
	{
		const Vector3 newScale = scale * rhs.scale;
		const Quaternion newRot = rot * rhs.rot;
		const Vector3 newPos = rot.Rotate(scale * rhs.pos) + pos;
		
		return Transform(newPos, newRot, newScale);
	}
	
	Transform operator*(const Transform & rhs)
	{
		return Concat(rhs);
	}
};

inline std::ostream & operator<<(std::ostream & o, const Transform & rhs)
{
	return o << "[pos = " << rhs.pos << ", quat = " << rhs.rot << ", scale = " << rhs.scale << "]";
}

#endif