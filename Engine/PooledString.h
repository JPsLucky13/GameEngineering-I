#pragma once
#include "StringPool.h"

namespace Engine {

class PooledString
{
public:
	explicit PooledString(StringPool * i_gGlobalStringPool, const char * i_pString) :
		gGlobalStringPool(i_gGlobalStringPool),
		m_pString(gGlobalStringPool->add(i_pString))
	{}

	PooledString(const PooledString & i_other) :
		gGlobalStringPool(i_other.gGlobalStringPool),
		m_pString(i_other.m_pString)
	{}

	PooledString & operator=(const PooledString & i_other)
	{
		m_pString = i_other.m_pString;
	}

	bool operator==(const PooledString & i_other)
	{
		return m_pString == i_other.m_pString;
	}

	bool operator==(const char * i_pString)
	{
		return m_pString == i_pString;
	}

	operator bool() const
	{
		return m_pString == nullptr;
	}

	const char * getString()
	{
		return m_pString;
	}


private:
	StringPool * gGlobalStringPool;
	const char * m_pString;

};

}
