#pragma once
#include "FixedBlockAllocator.h"
#include "Debug.h"

namespace Engine {

	FixedBlockAllocator::FixedBlockAllocator(size_t i_size, size_t i_numberOfBlocks, BlockAllocator * i_blockAllocator)
	{
		m_BlockSize = i_size;
		m_numberOfBlocks = i_numberOfBlocks;
		m_pBlockAllocator = i_blockAllocator;
		m_pAllocatorMemory = reinterpret_cast<uint8_t *>(i_blockAllocator->_alloc(i_size * i_numberOfBlocks));
	}

	FixedBlockAllocator::~FixedBlockAllocator()
	{
		//Notify the user of the outstanding allocations if there are any
		size_t firstClear;

		if (m_pAvailableBits->GetFirstClearBit(firstClear))
		{
			//Print Debug message
			DEBUG_LOG_MESSAGE("There is an outstanding allocation");
		}

		delete m_pBlockAllocator;
		m_pBlockAllocator = NULL;
		delete m_pAvailableBits;
		m_pAvailableBits = NULL;
		delete m_pAllocatorMemory;
		m_pAllocatorMemory = NULL;
	}

	void * FixedBlockAllocator::_alloc(size_t i_size)
	{
		if (i_size > m_BlockSize)
			return NULL;

		size_t i_firstAvailable;

		if (m_pAvailableBits->GetFirstSetBit(i_firstAvailable))
		{
			//Update the bit array to mark the block as being in use
			m_pAvailableBits->ClearBit(i_firstAvailable);

			//Calculate the address and return it to the user
			return m_pAllocatorMemory + (i_firstAvailable * m_BlockSize);
		}

		else
			return nullptr;
	}

	void FixedBlockAllocator::_free(void * i_ptr)
	{




	}


}