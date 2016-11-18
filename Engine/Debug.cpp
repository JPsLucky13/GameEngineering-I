
#include "Debug.h"
#include <stdarg.h>
#include <stdio.h>


namespace Engine {

	void PrintDebugMessage(const char* file, const char* function, const int line, const char* fmt, ...)
	{
		va_list arguments;
		va_start(arguments, fmt);
		printf("File name: %s, Function name: %s, Line: %d ", file, function, line);
		vprintf(fmt, arguments);
		va_end(arguments);
	}

}