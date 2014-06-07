#ifndef OC_MATRIX44_H
#define OC_MATRIX44_H

#include "transform.h"
#include "vector4.h"

struct Matrix44
{
	Matrix44(){}
	Matrix44(float f0, float f1, float f2, float f3,
		   float f4, float f5, float f6, float f7,
		   float f8, float f9, float f10, float f11,
		   float f12, float f13, float f14, float f15)
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
		f[9] = f9;
		f[10] = f10;
		f[11] = f11;
		f[12] = f12;
		f[13] = f13;
		f[14] = f14;
		f[15] = f15;
	}
	
	static Matrix44 FromMatrix33(const Matrix33 & mt33)
	{
		Matrix44 mt44 = Matrix44::Identity;
		mt44[0] = mt33[0];
		mt44[1] = mt33[1];
		mt44[2] = mt33[2];
		
		mt44[4] = mt33[4];
		mt44[5] = mt33[5];
		mt44[6] = mt33[6];
		
		mt44[8] = mt33.f[8];
		mt44[9] = mt33[9];
		mt44[10] = mt33[10];
		
		return mt44;
	}
	
	static Matrix44 FromTransform(const Transform & tr)
	{
		Matrix33 scaleMt = Matrix33::Identity;
		{
			scaleMt[0] = tr.scale.x;
			scaleMt[5] = tr.scale.y;
			scaleMt[10] = tr.scale.z;			
		}
		
		Matrix33 rotMt = tr.rot.toMatrix33();
		
		Matrix33 scaleRotMt = rotMt * scaleMt;
		Matrix44 finalMt = FromMatrix33(scaleRotMt);
		finalMt[12] = tr.pos.x;
		finalMt[13] = tr.pos.y;
		finalMt[14] = tr.pos.z;

		return finalMt;
	}
	
	void getRows(Vector4 & top, Vector4 & mid, Vector4 & mid2, Vector4 & bottom) const
	{
		top = Vector4(f[0], f[1], f[2], f[3]);
		mid = Vector4(f[4], f[5], f[6], f[7]);
		mid2 = Vector4(f[8], f[9], f[10], f[11]);
		bottom = Vector4(f[12], f[13], f[14], f[15]);
	}
	
	void getColumns(Vector4 & left, Vector4 & mid,Vector4 & mid2, Vector4 & right) const
	{
		left = Vector4(f[0], f[4], f[8], f[12]);
		mid = Vector4(f[1], f[5], f[9], f[13]);
		mid2 = Vector4(f[2], f[6], f[10], f[14]);
		right = Vector4(f[3], f[7], f[11], f[15]);
	}
	
	Matrix44 Multiply(const Matrix44 & rhs) const
	{
		Vector4 top,mid,mid2,bottom;
		Vector4 left,mid3,mid4, right;
		
		Matrix44 mt44;
		mt44[0] = top.Dot(left);
		mt44[1] = top.Dot(mid3);
		mt44[2] = top.Dot(mid4);
		mt44[3] = top.Dot(right);

		mt44[4] = mid.Dot(left);
		mt44[5] = mid.Dot(mid3);
		mt44[6] = mid.Dot(mid4);
		mt44[7] = mid.Dot(right);
		
		mt44[8] = mid2.Dot(left);
		mt44[9] = mid2.Dot(mid3);
		mt44[10] = mid2.Dot(mid4);
		mt44[11] = mid2.Dot(right);
		
		mt44[12] = bottom.Dot(left);
		mt44[13] = bottom.Dot(mid3);
		mt44[14] = bottom.Dot(mid4);
		mt44[15] = bottom.Dot(right);		
		
		return mt44;
	}
	
	Matrix44 operator*(const Matrix44 & rhs) const
	{
		return Multiply(rhs);
	}
	
	
	float operator[](int i) const { return f[i]; }
	float & operator[](int i){ return f[i]; }
	
	float f[16];
	
	static Matrix44 Identity;
};

#endif