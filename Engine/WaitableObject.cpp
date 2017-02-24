#include "WaitableObject.h"
namespace Engine
{ 
	WaitableObject & Engine::WaitableObject::operator=(const WaitableObject & i_other)
	{
		if (this != &i_other)
		{
			this->m_Handle = i_other.m_Handle;
		}
		return *this;
	}
}