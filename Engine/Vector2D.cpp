
#include "Vector2D.h"
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>

namespace Engine {



	Vector2D Vector2D::normalize()
	{
		float length = static_cast<float>(sqrt(m_x * m_x + m_y * m_y));
		assert(length != 0);
		Engine::Vector2D normalizedVector(m_x / length, m_y / length);
		return normalizedVector;
	}
}