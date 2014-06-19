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

	
	return 1;
}