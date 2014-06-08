#include <iostream>
#include "vector3.h"

int triangleTest()
{
	Vector3 x(1,1,0);
	Vector3 y(1,1,1);
	Vector3 z = y-x;
	
	std::cout << z << std::endl;
	
	return 0;
}