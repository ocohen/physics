#include <iostream>
#include <cstdlib>
#include <ctime>
#include "CImg.h"
#include "vector3.h"

using namespace cimg_library;

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

#define ARR_NUM(x) sizeof(x)/sizeof(x[0])

int convexHull()
{
	std::srand(time(NULL));
	
	int width = 500;
	int height = 500;
	
	Vector3 points[10];
	for(int i=0; i<ARR_NUM(points); ++i)
	{
		Vector3 & p = points[i];
		p.x = rand() % width;
		p.y = rand() % height;
		p.z = 0;
	}
	
	//compute hull
	
	//display
    CImg<unsigned char>  theImage(width,height,1,3,1);
	for(int i=0; i<ARR_NUM(points); ++i)
	{
		Vector3 & p = points[i];
		theImage(p.x, p.y, 0) = 255;
		theImage(p.x, p.y, 1) = 255;
		theImage(p.x, p.y, 2) = 255;
	}
    CImgDisplay main_disp(theImage); // display it
	std::cin.ignore();
	
	return 0;
}