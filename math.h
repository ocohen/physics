#ifndef OC_MATH_H
#define OC_MATH_H

#include <cmath>

#define SMALL_NUMBER 1e-4;

template <typename T> bool Abs(T val)
{
	return val >= 0 ? val : -val;
}

inline bool IsValue(float realValue, float targetValue)
{
	return Abs(realValue - targetValue) < SMALL_NUMBER;
}

inline bool IsZero(float val)
{
	return IsValue(val, 0);
}

#endif