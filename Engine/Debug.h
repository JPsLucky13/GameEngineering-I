#pragma once

#ifdef _DEBUG
#define DEBUG_LOG_MESSAGE(fmt,...) Engine::PrintDebugMessage(__FILE__,__FUNCTION__,__LINE__,fmt,__VA_ARGS__)
#define ASSERT(cond,message) assert((cond))
#else
#define DEBUG_LOG_MESSAGE(fmt,...) void(0)
#define ASSERT_MONSTER_NUMBER(cond,message) void (0)
#define ASSERT(cond,message) void(0)
#endif


namespace Engine {

	void PrintDebugMessage(const char* file, const char* function, const int line, const char* fmt, ...);

}