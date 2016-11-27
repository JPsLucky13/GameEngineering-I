#pragma once
#include "Math.h"

#define EPSILON .0001f
namespace Engine {

	class Math {

	};
inline bool IsNaN(float i_value);
inline bool floatEpsilonEqual(float i_lhs, float i_rhs, float epsilon = EPSILON);
}
#include "FloatCheck-inl.h"