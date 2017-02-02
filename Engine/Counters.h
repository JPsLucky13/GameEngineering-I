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



	private:
		long m_SmartRefCount;
		long m_WeakRefCount;
	};




}

#include "Counters-inl.h"