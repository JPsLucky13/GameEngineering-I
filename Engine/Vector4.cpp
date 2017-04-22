
#include "Vector4.h"
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>

namespace Engine {



	Vector4 Vector4::normalize()
	{

#ifdef _WIN64
		float length = static_cast<float>(sqrt(dot(m_vector, m_vector)));
		assert(length != 0);
		__m128 lengthVec = _mm_set_ps1(length);

		return Vector4(_mm_div_ps(m_vector, lengthVec));

#else
		float length = static_cast<float>(sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w));
		assert(length != 0);
		Engine::Vector4 normalizedVector(m_x / length, m_y / length, m_z / length, m_w / length);
		return normalizedVector;

#endif
	}
}