
#include "Vector2D.h"
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>

namespace Engine {


#ifdef _WIN64

#endif // _WIN64

	Vector2D Vector2D::normalize()
	{

#ifdef _WIN64
		float length = static_cast<float>(sqrt(dot(m_vector,m_vector)));
		assert(length != 0);
		__m128 lengthVec = _mm_set_ps1(length);

		return Vector2D(_mm_div_ps(m_vector, lengthVec));
#else
		float length = static_cast<float>(sqrt(m_x * m_x + m_y * m_y));
		assert(length != 0);
		Engine::Vector2D normalizedVector(m_x / length, m_y / length);
		return normalizedVector;
#endif
	}
}