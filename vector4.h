#ifndef OC_VECTOR4_H
#define OC_VECTOR4_H

#include <iosfwd>
#include "math.h"

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
	
	Vector4(){}
	Vector4(const Vector4 & rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w){}
	Vector4(float inX, float inY, float inZ, float inW) : x(inX), y(inY), z(inZ), w(inW){}
	
	float Dot(const Vector4 & rhs) const
	{
		return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
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
	
	const Vector4 SafeNormalize()
	{
		float l = Length();
		if(!::IsZero(l))
		{
			x /= l;
			y /= l;
			z /= l;
			w /= l;
		}
		
		return *this;
	}
	
	const Vector4 Normalize()
	{
		float l = Length();
		x /= l;
		y /= l;
		z /= l;
		w /= l;
		
		return *this;
	}
	
	Vector4 operator*(const Vector4 & rhs) const
	{
		return Vector4(x*rhs.x, y*rhs.y, z*rhs.z, w*rhs.w);
	}
	
	const Vector4 & operator*=(const Vector4 & rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}
	
	Vector4 operator+(const Vector4 & rhs) const
	{
		return Vector4(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
	}
	
	const Vector4 & operator+=(const Vector4 & rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}
	
	Vector4 operator-(const Vector4 & rhs) const
	{
		return Vector4(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
	}
	
	const Vector4 & operator-=(const Vector4 & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}
	
	const Vector4 & operator=(const Vector4 & rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}
	
	Vector4 operator*(float k) const
	{
		return Vector4(x*k, y*k, z*k, w*k);
	}
	
	const Vector4 & operator*=(float k)
	{
		x *= k;
		y *= k;
		z *= k;
		w *= k;
		
		return *this;
	}
	
	const Vector4 operator/(float k)
	{
		return Vector4(x/k, y/k, z/k, w/k);
	}
	
	const Vector4 & operator/=(float k)
	{
		x /= k;
		y /= k;
		z /= k;
		w /= k;
		
		return *this;
	}
	
	static Vector4 Zero;
};

inline Vector4 operator*(float k, const Vector4 & rhs)
{
	return rhs.operator*(k);
}

std::ostream & operator<<(std::ostream & o, const Vector4 & rhs);

#endif