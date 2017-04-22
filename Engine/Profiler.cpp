#include "Profiler.h"

namespace Engine {

	Profiler * Profiler::instance = NULL;


	Profiler::Profiler()
	{

	}

	Profiler * Profiler::Create()
	{
		if (instance == nullptr)
		{
			instance = new Profiler();
			return instance;
		}
		else
		{
			return instance;
		}
	}
	Profiler * Profiler::GetInstance()
	{
		return instance;
	}
	void Profiler::RegisterAccumulator(const char * i_pName, const Accumulator & i_Accumulator)
	{
		m_AllAccumulators.insert(std::pair<const char*, Accumulator *>(i_pName, const_cast<Accumulator *>(&i_Accumulator)));

	}


}

