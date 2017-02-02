#pragma once
#include "Counters.h"
#include <assert.h>

namespace Engine
{
	inline long Counters::AddSmartReference()
	{
		return ++m_SmartRefCount;
	}

	inline long Counters::ReleaseSmartReference()
	{
		assert(m_SmartRefCount > 0);

		if (--m_SmartRefCount == 0 && m_WeakRefCount == 0)
			delete this;

		return m_SmartRefCount;
	}

	inline long Counters::AddWeakReference()
	{
		return ++m_WeakRefCount;
	}

	inline long Counters::ReleaseWeakReference()
	{
		assert(m_WeakRefCount > 0);
		if (--m_WeakRefCount == 0)
		{
			if(m_SmartRefCount == 0)
				delete this;

		}
		return m_WeakRefCount;
	}

	inline long Counters::GetSmartRefCount()
 	{
		return m_SmartRefCount;
	}

	inline long Counters::GetWeakRefCount()
	{
		return m_WeakRefCount;
	}
}