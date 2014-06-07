#ifndef OC_QUATERNION_H
#define OC_QUATERNION_H

#include "math.h"
#include "vector3.h"

struct Quaternion
{
	Vector3 u;
	float w;
	
	Quaternion(){}
	Quaternion(const Quaternion & rhs) : u(rhs.u), w(rhs.w){}
	
	//we create quaternion around axis (x,y,z) with radian (alpha)
	Quaternion(Vector3(axis), float alpha)
	{
		//The quaternion can be represented as e^[(1/2 alpha)[Ux i + Uy j + Uz k] = cos(1/2 alpha) + [Ux i + Uy j + Uz k]sin(1/2 alpha)
		float length = axis.Length();
		if(IsZero(length))
		{
			u = Vector3::Zero;
		}else
		{
			float halfAngle = alpha / 2.f;
			float sinHalfAngle = sin(halfAngle);
			w = cos(halfAngle);
			float k = sinHalfAngle / length;
			u = k * axis;
		}
	}
	
	Vector3 Rotate(const Vector3 & v) const
	{
		//using formula for rotation from http://www.mathworks.com/help/aeroblks/quaternionrotation.html
		const float twoX2 = u.x*u.x * 2.f;
		const float twoY2 = u.y*u.y * 2.f;
		const float twoZ2 = u.z*u.z * 2.f;
		const float xy = u.x*u.y;
		const float wz = w*u.z;
		const float xz = u.x*u.z;
		const float wy = w*u.y;
		const float yz = u.y*u.z;
		const float wx = w*u.x;
		
		const Vector3 topRow(1.f-twoY2 - twoZ2, 2.f*(xy-wz), 2.f*(xz+wy));
		const Vector3 midRow(2.f*(xy+wz), (1.f-twoX2-twoZ2), 2.f*(yz-wx));
		const Vector3 botRow(2.f*(xz-wy), 2.f*(yz+wx), 1.f-twoX2-twoY2);
		
		return Vector3(topRow.Dot(v), midRow.Dot(v), botRow.Dot(v));
	}
	
	//Order is important. If we rotate v by the result quaternion, we'd first rotate v by rhs and then by this
	Quaternion Concat(const Quaternion & rhs) const
	{
		Quaternion q;
		q.w = w * rhs.w - u.Dot(rhs.u);
		q.u = u.Cross(rhs.u) + w*rhs.u + rhs.w*u;
		return q;	
	}
	
	Quaternion operator*(const Quaternion & rhs) const
	{
		return Concat(rhs);
	}
	
	static Quaternion Zero;
};

inline std::ostream & operator<<(std::ostream & o, const Quaternion & rhs)
{
	return o << "[" << rhs.u << " + " << rhs.w << "]";
}

#endif