#include "matrix33.h"
#include "matrix44.h"

Matrix33 Matrix33::Identity = Matrix33(1,0,0,
				 					 0,1,0,
								 	 0,0,1);

Matrix44 Matrix44::Identity = Matrix44(1,0,0,0,
				 					 0,1,0,0,
								 	 0,0,1,0,
									 0,0,0,1);