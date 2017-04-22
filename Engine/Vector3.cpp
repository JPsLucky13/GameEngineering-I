
#include "Vector3.h"
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>

namespace Engine {



	Vector3 Vector3::normalize()
	{

#ifdef _WIN64

		float length = static_cast<float>(sqrt(dot(m_vector,m_vector)));
		assert(length != 0);
		__m128 lengthVec = _mm_set_ps1(length);

		return Vector3(_mm_div_ps(m_vector,lengthVec));
#else
		float length = static_cast<float>(sqrt(m_x * m_x + m_y * m_y + m_z * m_z));
		assert(length != 0);
		Engine::Vector3 normalizedVector(m_x / length, m_y / length, m_z / length);
		return normalizedVector;
#endif

	}
	
}