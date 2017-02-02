#include "Counters.h"

namespace Engine
{
	Counters::Counters():
		m_SmartRefCount(0),
		m_WeakRefCount(0)
	{}

	Counters::~Counters()
	{
		//Gets deleted in decrement
	}


}