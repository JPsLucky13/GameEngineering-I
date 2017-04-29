#pragma once
#include <stdint.h>
#include <limits>
#include <stdio.h>
#include "Windows.h"
namespace Engine
{
	struct Accumulator
	{
		double m_Sum;
		uint64_t m_Count;
		float  m_Min, m_Max;


		Accumulator(const char * i_pName) :
			m_Sum(0.0),
			m_Count(0),
			m_Max((std::numeric_limits<float>::min)()),
			m_Min((std::numeric_limits<float>::max)())
		{
			//Engine::Profiler::GetInstance()->RegisterAccumulator(i_pName, *this);
		}

		~Accumulator()
		{
			const size_t	lenBuffer = 65;
			char			Buffer[lenBuffer];

			sprintf_s(Buffer, lenBuffer, "Total Time %f /n", m_Sum);
			OutputDebugStringA(Buffer);


			sprintf_s(Buffer, lenBuffer, "Average Time %f /n", average());
			OutputDebugStringA(Buffer);
		
		}


		void operator+=(float i_time)
		{
			m_Sum += i_time;
			m_Count++;

			if (i_time > m_Max)
				m_Max = i_time;
			else if (i_time < m_Min)
				m_Min = i_time;
		}

		float average()
		{
			return static_cast<float>(m_Sum / m_Count);
		}

	};


}