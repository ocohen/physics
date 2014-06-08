#include <iostream>
#include <cstring>
#include "funcs.h"

typedef int (*func)();

int main(int argc, const char ** argv)
{
	if(argc <= 1)
	{
		std::cout << "./a.out <test>" << std::endl;
		return 1;
	}
	
	const char * keys[] = {"triangle", "triarea", "parallelepipedvolume", "orient2d", "quadtest"};
	func funcs[] = {triangleTest, triangleArea, parallelepipedVolume, orient2d, quadTest};
	
	for(int i=0; i<sizeof(keys) / sizeof(char *); ++i)
	{
		if(strcmp(argv[1], keys[i]) == 0)
		{
			return funcs[i]();
		}
	}
	
	std::cout << "couldn't find (" << argv[1] << ") in commands:" << std::endl;
	for(int i=0; i<sizeof(keys) / sizeof(char*); ++i)
	{
		std::cout << " " << keys[i] << std::endl;
	}
	
	
	/*Quaternion q(Vector3(0.f,0.f,1.f), 3.14159/2);
	Quaternion q2(Vector3(0.f,0.f,1.f), 3.14159/2);

	Transform t1(Vector3(1,1,1), q, Vector3(2,2,2));
	Transform t2(Vector3(1,1,1), q, Vector3(.5,.5,.5));
	Transform t3 = t1*t2;

	Vector3 p(1,1,1);
	
	Vector3 p2 = t3.TransformPosition(p);
	std::cout << p2 << std::endl;
	
	Matrix44 mt44 = Matrix44::FromTransform(t3);
	std::cout << mt44 << std::endl;*/
	
	return 1;
}