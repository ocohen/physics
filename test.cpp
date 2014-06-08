#include <iostream>
#include "vector3.h"
#include "quaternion.h"
#include "transform.h"
#include "matrix44.h"
#include <stdio.h>

int main()
{
	Quaternion q(Vector3(0.f,0.f,1.f), 3.14159/2);
	Quaternion q2(Vector3(0.f,0.f,1.f), 3.14159/2);

	Transform t1(Vector3(1,1,1), q, Vector3(2,2,2));
	Transform t2(Vector3(1,1,1), q, Vector3(.5,.5,.5));
	Transform t3 = t1*t2;

	Vector3 p(1,1,1);
	
	Vector3 p2 = t3.TransformPosition(p);
	std::cout << p2 << std::endl;
	
	Matrix44 mt44 = Matrix44::FromTransform(t3);
	std::cout << mt44 << std::endl;
	
	return 0;
}