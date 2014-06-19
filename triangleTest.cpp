#include <iostream>
#include "vector3.h"
#include "matrix33.h"
#include "test.h"

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

class TriangleTest : public Test
{
public:
    bool Init()
    {
    	Vector3 a(1,0,0);
    	Vector3 b(1,1,0);
    	Vector3 c(0,0,0);
	
    	Vector3 p(1.f, 0.5f, 0.f);
	
    	//must check p is coplanar first

	
    	float u,v,w;
    	Barycentric(a,b,c,p,u,v,w);
	
    	if(InRange(v,0.f,1.f) && InRange(w,0.f,1.f) && v+w <= 1)	//can remove extra check since u=1-v-w
    	{
    		//need to make sure point is actually on triangle plane
    		if((p - a*u - b*v - c*w).IsZero())
    		{
    			std::cout << "in triangle" << std::endl;	
    			return false;
    		}
    	}

    	std::cout << "outside triangle" << std::endl;
        return false;
    }
};
TEST(TriangleTest, "triangletest");

class RenderTriangleTest : public Test
{
public:
    bool Tick(TinyRenderer::Renderer & renderer)
    {
    	Vector3 a(1,0,0);
    	Vector3 b(1,1,0);
    	Vector3 c(0,0,0);
	    
        float red[] = {1,0,0};
    
        renderer.DrawTriangle(&a.x, &b.x, &c.x);
        renderer.DrawPoint(&a.x, red);
        renderer.DrawPoint(&b.x, red);
        renderer.DrawPoint(&c.x, red);
        
        Vector3 pos(0,0,3);
        Vector3 up(0,1,0);
        renderer.SetCameraLookAt(&pos.x, &Vector3::Zero.x, &up.x);
	
        return false;
    }
};
TEST(RenderTriangleTest, "drawtriangle");

class Orient2d : public Test
{
    bool Init()
    {
    	//determine if p is to the left or right of ab
    	Vector3 a(1,0,1);
    	Vector3 b(0,1,1);
    	Vector3 p(0.5,0.4,1);
	
    	Matrix33 mt = Matrix33::FromRows(a,b,p);
    	bool apLeft = mt.Determinant() >= 0;
	
    	std::cout << "p to the left:" << apLeft << std::endl;
	
    	return false;
    }
};
TEST(Orient2d, "orient2d");


class TriangleArea : public Test
{
    bool Init()
    {
    	Vector3 a(1,0,0);
    	Vector3 b(1,1,0);
    	Vector3 c(0,0,0);
	
    	Vector3 ca = a-c;
    	Vector3 cb = b-c;
    	Vector3 n = ca.Cross(cb).Normalize();
	
    	Matrix33 mt = Matrix33::FromRows(ca,cb,n);
    	std::cout << mt << std::endl;
    	float area = mt.Determinant() / 2.f;
	
    	std::cout << "Area: " << area << std::endl;
	
    	return false;
    }
};

TEST(TriangleArea, "trianglearea");

class ParallelepipedVolume : public Test
{
    bool Init()
    {
    	Vector3 a(1,0,0);
    	Vector3 b(0,1,0);
    	Vector3 c(0,0,0);
    	Vector3 d(0,0,1);
	
    	Vector3 ca = a-c;
    	Vector3 cb = b-c;
    	Vector3 cd = d-c;
	
    	Matrix33 mt = Matrix33::FromRows(ca,cb,cd);
    	std::cout << mt << std::endl;
    	float area = mt.Determinant();
	
    	std::cout << "Volume: " << area << std::endl;
	
    	return false;
    }
};
TEST(ParallelepipedVolume, "parallelepiped");