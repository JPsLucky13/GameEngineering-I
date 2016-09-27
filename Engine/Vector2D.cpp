
#include "Vector2D.h"
#include <stdarg.h>
#include <stdio.h>

namespace Engine {

	Vector2D operator+(const Vector2D & input1, const Vector2D & input2)
	{
		return Vector2D(input1.x() + input2.x(), input1.y() + input2.y());
	}

	Vector2D operator-(const Vector2D & input1, const Vector2D & input2)
	{
		return Vector2D(input1.x() - input2.x(), input1.y() - input2.y());
	}

	bool operator==(const Vector2D & input1, const Vector2D & input2)
	{
		return (input1.x() == input2.x() && input1.y() == input2.y());
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