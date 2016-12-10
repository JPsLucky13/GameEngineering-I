#pragma once
#include "FloatCheck.h"



namespace Engine{
inline bool IsNaN(float i_value)
{
	//This is done to keep overly smart compilers from optimizing this whole function away
	volatile float val = i_value;
	return val != val;
}

inline bool floatEpsilonEqual(float i_lhs, float i_rhs, float epsilon)
{
	return fabs(i_rhs - i_lhs) < epsilon;
}

}