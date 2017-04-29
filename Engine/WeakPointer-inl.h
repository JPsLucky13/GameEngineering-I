#pragma once
#include "WeakPointer.h"
#include "Debug.h"

namespace Engine
{
	//Standard constructor
	template<class T>
	WeakPointer<T>::WeakPointer(T* i_ptr = NULL):
		m_pObject(i_ptr),
		m_pCounters(nullptr)
	{
		if (i_ptr != nullptr) {
			m_pCounters = new Counters();
			m_pCounters->AddWeakReference();
		}
	}

	//Destructor
	template<class T>
	WeakPointer<T>::~WeakPointer()
	{
		ReleaseCurrentReference();
	}

	//Copy constructor
	template<class T>
	WeakPointer<T>::WeakPointer(const WeakPointer & i_other):
		m_pObject(i_other.m_pObject),
		m_pCounters(i_other.m_pCounters)
	{
		m_pCounters->AddWeakReference();
	}

	//Copy constructor from smart pointer
	template<class T>
	WeakPointer<T>::WeakPointer(const SmartPointer<T> & i_other) :
		m_pObject(i_other.m_pObject),
		m_pCounters(i_other.m_pCounters)
	{
		m_pCounters->AddWeakReference();
	}

	//Reference assignment
	template<class T>
	WeakPointer<T>& WeakPointer<T>::operator=(const WeakPointer & i_other)
	{
		if (this != &i_other)
		{
			ReleaseCurrentReference();
			AcquireNewReference(i_other);
		}
		return *this;
	}

	//Acquire 
	template<class T>
	SmartPointer<T> WeakPointer<T>::Acquire() const {
		if (m_pCounters->GetSmartRefCount() > 0){
			return SmartPointer<T>(m_pObject, m_pCounters);
		}
		else
			return SmartPointer<T>(nullptr);
	}

	//Release reference
	template<class T>
	void WeakPointer<T>::ReleaseCurrentReference()
	{
		if (m_pCounters != nullptr)
		{
			m_pCounters->ReleaseWeakReference();
			if (m_pCounters->GetSmartRefCount() == 0 && m_pCounters->GetWeakRefCount() == 0)
			{
					delete m_pCounters;
					m_pCounters = nullptr;
			}
		}
		
	}

	//Acquire Reference
	template<class T>
	void WeakPointer<T>::AcquireNewReference(const WeakPointer & i_other)
	{
		m_pObject =i_other.m_pObject;
		m_pCounters =i_other.m_pCounters;
		m_pCounters->AddWeakReference();
	}
}