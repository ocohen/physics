#ifndef OC_MATRIX33_H
#define OC_MATRIX33_H

#include <stdio.h>
#include "vector3.h"

struct Matrix33
{
	Matrix33(){}
	Matrix33(float f0, float f1, float f2,
			 float f3, float f4, float f5,
			 float f6, float f7, float f8)
	{
		f[0] = f0;
		f[1] = f1;
		f[2] = f2;
		f[3] = f3;
		f[4] = f4;
		f[5] = f5;
		f[6] = f6;
		f[7] = f7;
		f[8] = f8;
	}
	
	static Matrix33 FromRows(const Vector3 & top, const Vector3 & mid, const Vector3 & bot)
	{
		return Matrix33(top.x, top.y, top.z,
						mid.x, mid.y, mid.z,
						bot.x, bot.y, bot.z);
	}
	
	static Matrix33 FromColumns(const Vector3 & left, const Vector3 & mid, const Vector3 & right)
	{
		return Matrix33(left.x, mid.x, right.x,
						left.y, mid.y, right.y,
						left.z, mid.z, right.z);
	}
	
	void GetRows(Vector3 & top, Vector3 & mid, Vector3 & bottom) const
	{
		top = Vector3(f[0], f[1], f[2]);
		mid = Vector3(f[3], f[4], f[5]);
		bottom = Vector3(f[6], f[7], f[8]);
	}
	
	void GetColumns(Vector3 & left, Vector3 & mid, Vector3 & right) const
	{
		left = Vector3(f[0], f[3], f[6]);
		mid = Vector3(f[1], f[4], f[7]);
		right = Vector3(f[2], f[5], f[8]);
	}
	
	float Determinant() const
	{
		//assume matrix is laid out as:
		//|u1 u2 u3|
		//|v1 v2 v3|
		//|w1 w2 w3|
		//Then determinant = u.(v x w)
		
		Vector3 u,v,w;
		GetRows(u,v,w);
		return u.Dot(v.Cross(w));		
	}
	
	Matrix33(const Matrix33 & rhs)
	{
		std::memcpy(f, rhs.f, sizeof(f));
	}
	
	Vector3 Multiply(const Vector3 & rhs) const
	{
		Vector3 topRow, midRow, botRow;
		GetRows(topRow, midRow, botRow);
		return Vector3(topRow.Dot(rhs), midRow.Dot(rhs), botRow.Dot(rhs));
	}
	
	Vector3 operator*(const Vector3 & rhs) const
	{
		return Multiply(rhs);
	}
	
	Matrix33 Multiply(const Matrix33 & rhs) const
	{
		//this is a very simple implementation
		Matrix33 mt;
		Vector3 top,mid,bottom;
		Vector3 left,mid2,right;
		
		GetRows(top,mid,bottom);
		rhs.GetColumns(left,mid2,right);
		
		mt[0] = top.Dot(left);
		mt[1] = top.Dot(mid2);
		mt[2] = top.Dot(right);
		
		mt[3] = mid.Dot(left);
		mt[4] = mid.Dot(mid2);
		mt[5] = mid.Dot(right);
		
		mt[6] = bottom.Dot(left);
		mt[7] = bottom.Dot(mid2);
		mt[8] = bottom.Dot(right);
		
		return mt;
	}
	
	Matrix33 operator*(const Matrix33 & rhs) const
	{
		return Multiply(rhs);
	}
	
	float operator[](int i) const { return f[i]; }
	float & operator[](int i){ return f[i]; }
	
	float f[9];
	
	static Matrix33 Identity;
};

std::ostream & operator<<(std::ostream & o, const Matrix33 & rhs);

#endif