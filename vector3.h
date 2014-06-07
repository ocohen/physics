#ifndef OC_VECTOR3_H
#define OC_VECTOR3_H

#include <iostream>
#include "math.h"

struct Vector3
{
	float x;
	float y;
	float z;
	
	Vector3(){}
	Vector3(const Vector3 & rhs) : x(rhs.x), y(rhs.y), z(rhs.z){}
	Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ){}
	
	float Dot(const Vector3 & rhs) const
	{
		return x*rhs.x + y*rhs.y + z*rhs.z;
	}
	
	Vector3 Cross(const Vector3 & rhs) const
	{
		const Vector3 & u = *this;
		const Vector3 & v = rhs;
		
		float i = u.y*v.z - u.z*v.y;
		float j = u.z*v.x - u.x*v.z;
		float k = u.x*v.y - u.y*v.x;
		
		return Vector3(i,j,k);
	}
	
	bool IsZero() const
	{
		return ::IsZero(x) && ::IsZero(y) && ::IsZero(z);
	}
	
	float Length2() const
	{
		return this->Dot(*this);
	}
	
	float Length() const
	{
		return sqrt(Length2());
	}
	
	Vector3 operator+(const Vector3 & rhs) const
	{
		return Vector3(x+rhs.x, y+rhs.y, z+rhs.z);
	}
	
	const Vector3 & operator+=(const Vector3 & rhs)
	{
		x+= rhs.x;
		y+= rhs.y;
		z+= rhs.z;
		return *this;
	}
	
	Vector3 operator-(const Vector3 & rhs) const
	{
		return Vector3(x-rhs.x, y-rhs.y, z-rhs.z);
	}
	
	const Vector3 & operator-=(const Vector3 & rhs)
	{
		x-= rhs.x;
		y-= rhs.y;
		z-= rhs.z;
		return *this;
	}
	
	const Vector3 & operator=(const Vector3 & rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
	
	Vector3 operator*(float k) const
	{
		return Vector3(x*k, y*k, z*k);
	}
	
	const Vector3 & operator*=(float k)
	{
		x *= k;
		y *= k;
		z *= k;
		
		return *this;
	}
	
	const Vector3 operator/(float k)
	{
		return Vector3(x/k, y/k, z/k);
	}
	
	const Vector3 & operator/=(float k)
	{
		x /= k;
		y /= k;
		z /= k;
		
		return *this;
	}
	
	static Vector3 Zero;
};

inline Vector3 operator*(float k, const Vector3 & rhs)
{
	return rhs.operator*(k);
}

inline std::ostream & operator<<(std::ostream & o, const Vector3 & rhs)
{
	return o << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
}

#endif