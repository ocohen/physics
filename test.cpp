#include <iostream>
#include "vector3.h"
#include "quaternion.h"

int main()
{
	Quaternion q(Vector3(0.f,0.f,1.f), 3.14159/2);
	Vector3 p1(1.f,0.f,0.f);
	Vector3 p2(0.f,1.f,0.f);
	Vector3 p3(0.3,0.3, 0.f);

	std::cout << q << std::endl;
	
	std::cout << p1 << std::endl;
	std::cout << p2 << std::endl;
	std::cout << p3 << std::endl;
	
	p1 = q.Rotate(p1);
	p2 = q.Rotate(p2);
	p3 = q.Rotate(p3);

	std::cout << p1 << std::endl;
	std::cout << p2 << std::endl;
	std::cout << p3 << std::endl;

	
	return 0;
}