#pragma once
#include "SmartPointer.h"

namespace Engine {

	//standard constructor
	template<class T>
	SmartPointer<T>::SmartPointer(T* i_ptr = NULL) :
		m_pObject(i_ptr)
	{}

	//Destructor
	template<class T>
	SmartPointer<T>::~SmartPointer() {
		m_pObject(nullptr);
		m_pCounters(nullptr);
	
	}

	//copy constructor
	template<class T>
	SmartPointer<T>::SmartPointer(const SmartPointer & i_other) :
		m_pObject(i_other.m_pObject),
		m_pCounters(i_other.m_pCounters)
	{
		m_pCounters->AddSmartReference();
	}

	//Standard constructor
	template<class T>
	SmartPointer<T>::SmartPointer(T* i_ptr, Counters * i_pCounters) :
		m_pObjects(i_ptr),
		m_pCounters(i_pCounters)
	{}


	//move constructor
	template<class T>
	SmartPointer<T>::SmartPointer(SmartPointer && move):
		m_pObject(move.m_pObject),
		m_pCounters(move.m_pCounters)
	{
		move.m_pObject = nullptr;
		move.m_pCounters = nullptr;
	}

	//Reference assignment
	template<class T>
	SmartPointer<T>::&operator=(const SmartPointer & i_other)
	{
		ReleaseCurrentReference();
		AcquireNewReference(i_other);

		return *this;
	}

	//Arrow operator
	template<class T>
	T* SmartPointer<T>::operator->()
	{
		return m_pObject;
	}

	//Dereferencer
	template<class T>
	T & SmartPointer<T>::operator*()
	{
		assert(m_pObject != nullptr);
		return *m_pObject;
	}

	//Check the underlying pointer is not null
	template<class T>
	SmartPointer<T>::operator bool() const
	{
		return m_pObject != nullptr;
	}

	//Compare
	template<class T>
	bool SmartPointer<T>::operator==(const SmartPointer & i_other)const
	{
		if (m_pObject == i_other.m_pObject)
			return true;
		else
			return false;
	}

	//Release current reference
	template<class T>
	void SmartPointer<T>::ReleaseCurrentReference()
	{
		m_pCounters->ReleaseSmartReference();
		if (m_pCounters->m_SmartRefCount == 0 && m_pObject != nullptr)
			delete m_pObject;
			
		m_pObject = nullptr;
		m_pCounters = nullptr;
	}

	//Acquire new Reference
	template<class T>
	void SmartPointer<T>::AcquireNewReference(const SmartPointer & i_other)
	{
		m_pObject(i_other.m_pObject);
		m_pCounters(i_other.m_pCounters);
		m_pCounters->AddSmartReference();
	}
}