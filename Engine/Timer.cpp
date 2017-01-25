#include "Timer.h"

float Engine::Timer::CalcLastFrameTime_ms()
{

	float g_LastFrameTime_ms;

	//Grab the CPU Tick Counter
	long currentTick = GetCounter();

	if (g_LastFrameStartTick)
	{
		//How many ticks have elapsed since we last did this
		long elapsedTicks = (currentTick - g_LastFrameStartTick);

		//Calculate the frame time - converting the ticks to ms.
		g_LastFrameTime_ms = static_cast<float>(elapsedTicks / QueryPerformanceFrequency(&counterResult));
	}
	else {

		g_LastFrameTime_ms = 13.3f;//Assume a 60Hz frame for first call.
	
	}
	//Note start of this frame
	g_LastFrameStartTick = currentTick;

	return g_LastFrameTime_ms;

	
}

float Engine::Timer::GetLastFrameTime_ms()
{

#if defined(CONSTANT_FRAMETIME)
	return DESIRED_FRAMETIME_MS;
#elif defined (CLAMP_FRAMETIME)
	if (g_LastFrameTime_ms > MAX_FRAMETIME_MS)
		return MAX_FRAMETIME_MS;
	else
		return CalcLastFrameTime_ms();
#else
	return CalcLastFrameTime_ms();
#endif
}

long Engine::Timer::GetCounter()
{
	
	QueryPerformanceCounter(&counterResult);

	return static_cast<long>(counterResult.QuadPart);
}
