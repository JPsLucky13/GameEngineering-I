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
		~WeakPointer();
		WeakPointer(const WeakPointer & i_other);
		WeakPointer(const SmartPointer<T> & i_other);
		WeakPointer &operator=(const WeakPointer & i_other);
		SmartPointer<T>Acquire() const;
		void ReleaseCurrentReference();

	private:
		T * m_pObject;
		Counters * m_pCounters;
		void AcquireNewReference(const WeakPointer & i_other);

		};
}

#include "WeakPointer-inl.h"