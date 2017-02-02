#pragma once
#include "SmartPointer.h"
#include "Counters.h"

namespace Engine
{
	template<class T>
	class WeakPointer
	{
	public:
		WeakPointer(T* i_ptr = NULL);
		WeakPointer(const WeakPointer & i_other);
		WeakPointer(const SmartPointer & i_other);
		WeakPointer &operator=(const WeakPointer & i_other);
		SmartPointer<T>Acquire() const;
		void ReleaseCurrentReference();
		void AcquireNewReference(const WeakPointer & i_other);

private:
	T * m_pObject;
	Counters * m_pCounters;

	};
}

#include "WeakPointer-inl.h"