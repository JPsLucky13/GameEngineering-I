#include "Debug.h"
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>


namespace Engine {

	void PrintDebugMessage(const char* file, const char* function, const int line, const char* fmt, ...)
	{
		va_list arguments;
		va_start(arguments, fmt);
		printf("File name: %s, Function name: %s, Line: %d ", file, function, line);
		vprintf(fmt, arguments);
		va_end(arguments);
	}

	int PrintOutPutLog(const char* file, const char* func, const int line, const char* fmt, ...)
	{
		const size_t tempLength = 1024 + 1024;
		char temp[tempLength] = { 0 };
		sprintf_s(temp, fmt);
		va_list argp;
		const size_t outputLength = tempLength + 1024;
		char output[outputLength] = { 0 };
		va_start(argp, fmt);
		sprintf_s(temp, tempLength, "File: %s\n", file);
		OutputDebugStringA(temp);
		sprintf_s(temp, tempLength, "Func: %s\n", func);
		OutputDebugStringA(temp);
		sprintf_s(temp, tempLength, "Line: %d\n", line);
		OutputDebugStringA(temp);
		vsprintf_s(output, outputLength, fmt, argp);
		va_end(argp);
		OutputDebugStringA(output);
		OutputDebugStringA("\n");
		return 0;
	}

}