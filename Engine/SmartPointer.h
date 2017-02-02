#pragma once
#include <assert.h>
#include "Counters.h"
namespace Engine{

template<class T>
class SmartPointer
{


public:
	SmartPointer(T* i_ptr = NULL);
	~SmartPointer();
	SmartPointer(const SmartPointer & i_other);
	SmartPointer(T* i_ptr, Counters * m_pCounters);
	SmartPointer(SmartPointer && move);
	SmartPointer &operator=(const SmartPointer & i_other);

	//member access operator 
	T* operator->();

	//indirection operator
	T & operator*();

	operator bool() const;

	bool operator==(const SmartPointer & i_other)const;


	void ReleaseCurrentReference();


private:
	T* m_pObject;
	Counters * m_pCounters;
	template<class T>
	friend class WeakPointer;
	void AcquireNewReference(const SmartPointer & i_other);

};
}
#include "SmartPointer-inl.h"