#pragma once
#include "FixedBlockAllocator.h"
#include "Debug.h"
#include "NewDelete.h"

namespace Engine {

	FixedBlockAllocator::FixedBlockAllocator(size_t i_size, size_t i_numberOfBlocks, BlockAllocator * i_blockAllocator)
	{
		m_BlockSize = i_size;
		m_numberOfBlocks = i_numberOfBlocks;
		m_pBlockAllocator = i_blockAllocator;
		m_pAllocatorMemory = reinterpret_cast<uint8_t *>(i_blockAllocator->_alloc(i_size * i_numberOfBlocks));
		m_pAvailableBits = new(i_blockAllocator) BitArray(i_numberOfBlocks,i_blockAllocator,true);
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

		//free the memory used by the allocator
		_aligned_free(m_pAllocatorMemory);

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
		size_t position = (reinterpret_cast<uint8_t *>(i_ptr) - m_pAllocatorMemory) / m_BlockSize;

		if (!isValidPointer(i_ptr) || !m_pAvailableBits->IsBitClear(position))
		{

#ifdef _DEBUG
			DEBUG_LOG_MESSAGE("Pointer is not valid");
#endif // DEBUG

		}

		else {
			//Update the bit array to mark the block as available
			m_pAvailableBits->SetBit(position);
		}


	}

	bool FixedBlockAllocator::isValidPointer(void * i_ptr)
	{

		if (m_pAllocatorMemory <= i_ptr && i_ptr < reinterpret_cast<uint8_t*>(m_pAllocatorMemory) + (m_BlockSize * m_numberOfBlocks))
		{
			return true;
		}
		else
			return false;
	}


}