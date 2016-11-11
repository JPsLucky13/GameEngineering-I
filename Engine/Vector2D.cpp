
#include "Vector2D.h"
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>

namespace Engine {

	Vector2D Vector2D::normalize()
	{
		float length = static_cast<float>(sqrt(m_x * m_x + m_y * m_y));
		Engine::Vector2D normalizedVector(m_x / length, m_y / length);
		return normalizedVector;
	}



	void PrintDebugMessage(const char* file, const char* function, const int line, const char* fmt, ...)
	{
		va_list arguments;
		va_start(arguments,fmt);
		printf("File name: %s, Function name: %s, Line: %d ", file, function, line);
		vprintf(fmt,arguments);
		va_end(arguments);
	}

}