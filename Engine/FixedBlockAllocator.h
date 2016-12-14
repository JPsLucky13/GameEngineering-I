#pragma once
#include "BitArray.h"
#include "BlockAllocator.h"
#include <stdint.h>

namespace Engine {

	class FixedBlockAllocator
	{
	
	public:

		FixedBlockAllocator(size_t i_size, size_t i_numberOfBlocks, BlockAllocator * i_blockAllocator);

		~FixedBlockAllocator();


		//Allocate memory
		void * _alloc(size_t i_size);

		//Free memory
		void _free(void * i_ptr);

		bool isValidPointer(void * i_ptr);



	private:
		
		BitArray * m_pAvailableBits;
		size_t m_BlockSize;

		size_t m_numberOfBlocks;

		//pointer to the block allocator to be used
		BlockAllocator * m_pBlockAllocator;

		//The pointer to where the fixed sized allocator is in memory
		uint8_t * m_pAllocatorMemory;

	};


}