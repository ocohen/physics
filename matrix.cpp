#include <iostream>
#include "matrix33.h"
#include "matrix44.h"

Matrix33 Matrix33::Identity = Matrix33(1,0,0,
				 					 0,1,0,
								 	 0,0,1);

Matrix44 Matrix44::Identity = Matrix44(1,0,0,0,
				 					 0,1,0,0,
								 	 0,0,1,0,
									 0,0,0,1);

std::ostream & operator<<(std::ostream & o, const Matrix44 & rhs)
{
	Vector4 top, mid, mid2, bottom;
	rhs.getRows(top,mid,mid2,bottom);

	return o << "[ " << top << std::endl << mid << std::endl << " " << mid2 << std::endl << " " <<  bottom << " ]" << std::endl;
}
								 