#pragma once

#include "Accumulator.h"
#include <map>

namespace Engine {

	class Profiler {


		std::map<const char *, Accumulator *> m_AllAccumulators;


	public:

		static Profiler * Create();
		static Profiler * GetInstance();
		
		void RegisterAccumulator(const char * i_pName, const Accumulator & i_Accumulator);

	private:

		static Profiler * instance;
		Profiler();

	};

	
}