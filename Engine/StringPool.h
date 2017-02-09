#pragma once
#include <stdint.h>
#include "BlockAllocator.h"

namespace Engine
{
	class StringPool
	{
	public:
		StringPool * create(size_t i_bytesInPool, BlockAllocator * i_pBlockAllocator);
		~StringPool();

		//find string in pool - adding it if it's not there
		const char * add(const char * i_pString);
		//find string in pool - don't add if it's not there
		const char * find(const char * i_pString);

	private:
		StringPool(uint8_t * i_pPool, size_t i_sizePool);

		//The pointers to the block of memory
		uint8_t * m_pStartBuffer;
		uint8_t * m_pEndStrings;
		uint8_t * m_pEndBuffer;
		BlockAllocator * m_pBlockAllocator;

	};



}