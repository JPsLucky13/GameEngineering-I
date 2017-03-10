
#include "Vector3.h"
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>

namespace Engine {



	Vector3 Vector3::normalize()
	{
		float length = static_cast<float>(sqrt(m_x * m_x + m_y * m_y + m_z * m_z));
		assert(length != 0);
		Engine::Vector3 normalizedVector(m_x / length, m_y / length, m_z / length);
		return normalizedVector;
	}
}