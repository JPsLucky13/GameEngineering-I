
#include "Vector4.h"
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>

namespace Engine {



	Vector4 Vector4::normalize()
	{
		float length = static_cast<float>(sqrt(dot(m_vector, m_vector)));
		assert(length != 0);
		__m128 lengthVec = _mm_set_ps1(length);

		return Vector4(_mm_div_ps(m_vector, lengthVec));
	}
}