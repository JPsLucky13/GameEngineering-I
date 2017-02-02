#pragma once
#include "WeakPointer.h"
namespace Engine
{
	//Standard constructor
	template<class T>
	WeakPointer::WeakPointer(T* i_ptr = NULL):
		m_pObject(i_ptr)
	{
	}

	//Copy constructor
	template<class T>
	WeakPointer::WeakPointer(const WeakPointer & i_other):
		m_pObject(i_other.m_pObject),
		m_pCounters(i_other.m_pCounters)
	{
		m_pCounters->AddWeakReference();
	}

	//Copy constructor from smart pointer
	template<class T>
	WeakPointer::WeakPointer(const SmartPointer & i_other) :
		m_pObject(i_other.m_pObject),
		m_pCounters(i_other.m_pCounters)
	{
		m_pCounters->AddWeakReference();
	}

	//Reference assignment
	template<class T>
	WeakPointer::&operator=(const WealPointer & i_other)
	{
		ReleaseCurrentReference();
		AcquireNewReference(i_other);

		return *this;
	}

	//Acquire 
	template<class T>
	SmartPointer<T> WeakPointer::Acquire() const {
		if (m_pCounters->m_SmartRefCount > 0)
			return SmartPointer(m_pObjects, m_pCounters);
		else
			return SmartPointer(nullptr);
	}

	//Release reference
	template<class T>
	void WeakPointer<T>::ReleaseCurrentReference()
	{
		m_pCounters->ReleaseWeakReference();
		m_pObject = nullptr;
		m_pCounters = nullptr;
	}

	//Acquire Reference
	template<class T>
	void WeakPointer<T>::AcquireNewReference(const WeakPointer & i_other)
	{
		m_pObject(i_other.m_pObject);
		m_pCounters(i_other.m_pCounters);
		m_pCounters->AddWeakReference();
	}
}