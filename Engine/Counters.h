#pragma once
namespace Engine {

	class Counters {

	public :
		Counters();
		~Counters();


		inline long AddSmartReference();
		inline long ReleaseSmartReference();
		inline long AddWeakReference();
		inline long ReleaseWeakReference();

		inline long GetSmartRefCount();
		inline long GetWeakRefCount();

	private:
		long m_SmartRefCount;
		long m_WeakRefCount;
	};




}

#include "Counters-inl.h"