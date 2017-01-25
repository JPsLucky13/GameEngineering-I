#pragma once
#include <Windows.h>
#define DESIRED_FPS 60.0f
#define DESIRED_FRAMETIME_MS (1000.0f / DESIRED_FPS)
#define MAX_FRAMETIME_MS (2 * DESIRED_FRAMETIME_MS)

namespace Engine {

	class Timer
	{


	public:



		//The last frame time calculated in ms
		float CalcLastFrameTime_ms();
		//Get the last frame time
		float GetLastFrameTime_ms();

		long GetCounter();

	private:
		LARGE_INTEGER counterResult;
		long g_LastFrameStartTick;
	};



}
