#include <iostream>
#include "vector3.h"

void Barycentric(const Vector3 & A, const Vector3 & B, const Vector3 & C, const Vector3 & P, float & u, float & v, float & w)
{
	//we write barycentric coordinates as P = uA + vB + wC, where u+v+w = 1
	//=> P = A + v(B-A) + w(C-A)
	//=> (P-A) = v(B-A) + w(C-A)
	//=> V2 = vV0 + wV1
	//use dot product to get system of equations
	
	//V2.V0 = vV0.V0 + wV1.V0
	//V2.V1 = vV0.V1 + wV1.V1
	
	//solve for v,w => solve for u = (1-v-w)
	
	Vector3 V0 = B-A;
	Vector3 V1 = C-A;
	Vector3 V2 = P-A;
	
	float v0v2 = V2.Dot(V0);
	float v1v2 = V2.Dot(V1);
	
	float v0v0 = V0.Dot(V0);
	float v0v1 = V0.Dot(V1);
	float v1v1 = V1.Dot(V1);
	
	//system of equations looks like this:
	//|V0.V0 V1.V0|  |v|   |V2.V0|
	//|V0.V1 V1.V1|  |w| = |V2.V1|
	
	//solve for v,w using cramer's rule
	float denom = Determinant(v0v0, v0v1, v0v1, v1v1);
	
	if(IsZero(denom))
	{
		std::cout << "not a triangle, points are colinear" << std::endl;
		return;
	}
	
	v = Determinant(v0v2, v0v1, v1v2, v1v1) / denom;
	w = Determinant(v0v0, v0v2, v0v1, v1v2) / denom;
	u = 1-v-w;
}

int triangleTest()
{
	Vector3 a(1,0,0);
	Vector3 b(1,1,0);
	Vector3 c(0,0,0);
	
	Vector3 p(1.f, 0.5f, 0.f);
	
	float u,v,w;
	Barycentric(a,b,c,p,u,v,w);
	
	if(InRange(v,0.f,1.f) && InRange(w,0.f,1.f) && v+w <= 1)	//can remove extra check since u=1-v-w
	{
		//need to make sure point is actually on triangle plane
		if((p - a*u - b*v - c*w).IsZero())
		{
			std::cout << "in triangle" << std::endl;	
			return 0;
		}
	}

	std::cout << "outside triangle" << std::endl;
	
	return 0;
}