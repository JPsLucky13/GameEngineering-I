#pragma once
#include "Accumulator.h"
#include "ScopedTimer.h"


//The concatenation helper
#define CONCAT_HELPER(left,right) left##right
#define CONCAT(left,right) CONCAT_HELPER(left,right)

//Definition for profiling
#if defined(ENABLE_PROFILING)

#define PROFILE_UNSCOPED(name)	\
	static Engine::Accumulator CONCAT(__Accumulator, __LINE__)(name); Engine::ScopedTimer CONCAT(__Timer, __LINE__)(CONCAT(__Accumulator, __LINE__));

#define PROFILE_SCOPE_BEGIN(name)	\
	static Engine::Accumulator CONCAT(__Accumulator, __LINE__)(name); Engine::ScopedTimer CONCAT(__Timer, __LINE__)(CONCAT(__Accumulator, __LINE__));

#define PROFILE_SCOPE_END()

#else //ENABLE_PROFILING not defined

#define PROFILE_SCOPE_BEGIN(str) __noop
#define PROFILE_SCOPE_END()		 __noop
#define PROFILE_UNSCOPED(str)	 __noop

#endif //ENABLE_PROFILING

