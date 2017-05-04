
#include "Vector2D.h"
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>

namespace Engine {
	Vector2D Vector2D::normalize()
	{
		float length = static_cast<float>(sqrt(dot(m_vector,m_vector)));
		assert(length != 0);
		__m128 lengthVec = _mm_set_ps1(length);
		return Vector2D(_mm_div_ps(m_vector, lengthVec));

	}
}