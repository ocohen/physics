#include <iostream>
#include "vector3.h"

int quadTest()
{
	Vector3 a(0,0,0);
	Vector3 b(1,0,0);
	Vector3 c(1,1,0);
	Vector3 d(0,1,0);
	
	//checking the winding of BDA is opposite of BDC
	Vector3 bd = d-b;
	Vector3 ba = a-b;
	Vector3 bc = c-b;
	
	Vector3 bda = bd.Cross(ba);
	Vector3 bdc = bd.Cross(bc);
	
	bool bConvex = (bd.Cross(ba)).Dot( bd.Cross(bc)) < 0.f;
	
	std::cout << "convex:" << bConvex << std::endl;
	
	return 0;
}