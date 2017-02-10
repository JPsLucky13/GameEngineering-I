#pragma once

#include "PooledString.h"


namespace Engine {

	class HashedString {

	public: 
		HashedString(const char * i_pString) :
			m_pString(i_pString)
		{}


		HashedString(PooledString & i_PooledString) :
			m_pString(i_PooledString.getString())
		{}


		HashedString(const HashedString & i_other):
			m_pString(i_other.m_pString)
		{}

		HashedString & operator= (const HashedString & i_other)
		{
			m_pString = i_other.m_pString;
		}

		bool operator==(PooledString & i_other)
		{
			return m_pString == i_other.getString();
		}


		bool operator==(const HashedString & i_other)
		{
			return m_pString == i_other.m_pString;
		}

		bool operator==(const char * i_pString)
		{
			return m_pString == i_pString;
		}

		operator bool()
		{
			return m_pString == nullptr;
		}

		unsigned int Hash(const char * i_string);
		unsigned int Hash(const void * i_bytes, size_t i_byteCount);

	private:
		const char * m_pString;

	};

}