#pragma once
#include <Windows.h>
#define DESIRED_FPS 60.0f
#define DESIRED_FRAMETIME_S (1.0f / DESIRED_FPS)
#define MAX_FRAMETIME_MS (2 * DESIRED_FRAMETIME_S)

namespace Engine {

	class Timer
	{


	public:

		Timer();
		~Timer();


		//The last frame time calculated in ms
		float CalcLastFrameTime_ms();
		//Get the last frame time
		float GetLastFrameTime_ms();

		double GetCounter();
		double GetFrequency();

	private:
		double g_LastFrameStartTick;
		double m_fFrequency;
	};



}
