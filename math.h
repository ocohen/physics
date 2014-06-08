#ifndef OC_MATH_H
#define OC_MATH_H

#include <cmath>

#define SMALL_NUMBER 1e-4;

template <typename T> bool Abs(T val)
{
	return val >= 0 ? val : -val;
}

template <typename T> bool InRange(T val, T min, T max)
{
	return val >= min && val <= max;
}

inline bool IsValue(float realValue, float targetValue)
{
	return Abs(realValue - targetValue) < SMALL_NUMBER;
}

inline bool IsZero(float val)
{
	return IsValue(val, 0);
}

inline float Determinant(float f0, float f1,
						 float f2, float f3)
{
	return f0*f3 - f1*f2;
}

#endif