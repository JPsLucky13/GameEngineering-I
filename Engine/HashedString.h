#pragma once

#include "PooledString.h"


namespace Engine {

	class HashedString {

	public: 
		HashedString(const char * i_pString) :
			m_hash(Hash(i_pString))
		{
		
		}


		HashedString(PooledString & i_PooledString) :
			m_hash(Hash(i_PooledString.getString()))
		{}


		HashedString(const HashedString & i_other):
			m_hash(i_other.m_hash)
		{}

		HashedString & operator= (const HashedString & i_other)
		{
			m_hash = i_other.m_hash;
		}

		bool operator==(PooledString & i_other)
		{
			return m_hash == Hash(i_other.getString());
		}


		bool operator==(const HashedString & i_other)
		{
			return m_hash == i_other.m_hash;
		}

		bool operator==(const char * i_pString)
		{
			return m_hash == Hash(i_pString);
		}

		bool operator<(const HashedString& i_other) const
		{
			return m_hash < i_other.m_hash;
		}

		//operator bool()
		//{
		//	return m_hash == nullptr;
		//}

		unsigned int Hash(const char * i_string);
		unsigned int Hash(const void * i_bytes, size_t i_byteCount);

	private:
		int m_hash;

	};

}