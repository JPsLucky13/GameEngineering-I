
#include "Vector4.h"
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>

namespace Engine {



	Vector4 Vector4::normalize()
	{
		float length = static_cast<float>(sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w));
		assert(length != 0);
		Engine::Vector4 normalizedVector(m_x / length, m_y / length, m_z/length, m_w / length);
		return normalizedVector;
	}
}