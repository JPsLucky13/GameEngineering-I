#pragma once
#include "Timer.h"
#include "Profiler.h"

namespace Engine {
	class ScopedTimer {

		double m_Start;
		Accumulator * m_pAccumulator;
		const char * m_pScopeName;

	public:
		ScopedTimer(Accumulator & i_MyAccumulator) :
			m_Start(Engine::Timer::GetInstance()->GetCounter()),
			m_pAccumulator(&i_MyAccumulator)
		{}

		~ScopedTimer()
		{
			*m_pAccumulator += static_cast<float>(Engine::Timer::GetInstance()->GetTimeDiff_s(Engine::Timer::GetInstance()->GetCounter()));
			const size_t	lenBuffer = 65;
			char			Buffer[lenBuffer];

			sprintf_s(Buffer, lenBuffer, "Average Time %f", m_pAccumulator->average());
			OutputDebugStringA(Buffer);
		}

	};

}