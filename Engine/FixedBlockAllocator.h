#pragma once
#include "BlockAllocator.h"
#include <stdint.h>
#include "BitArray.h"

namespace Engine {

	class FixedBlockAllocator
	{
	
	public:

		FixedBlockAllocator(size_t i_size, size_t i_numberOfBlocks, BlockAllocator * i_blockAllocator);

		~FixedBlockAllocator();

		//Get the Bit array 
		const BitArray * GetBitArray() {return m_pAvailableBits;}

		//Get the number of blocks
		const size_t GetTotalNumBlocks() { return m_numberOfBlocks; }

		//Get the block size
		const size_t GetBlockSize() { return m_BlockSize; }

		

		//Allocate memory
		void * _alloc(size_t i_size);

		//Free memory
		void _free(void * i_ptr);

		bool isValidPointer(void * i_ptr);

#ifdef _DEBUG
		//Get the number of available blocks
		const size_t GetTotalAvailableBlocks() { return m_availableBlocks; }
		
		void PrintAvailableBlocks();


#endif // _DEBUG

	private:
		
		BitArray* m_pAvailableBits;

		size_t m_BlockSize;

		size_t m_numberOfBlocks;



		//pointer to the block allocator to be used
		BlockAllocator * m_pBlockAllocator;

		//The pointer to where the fixed sized allocator is in memory
		uint8_t * m_pAllocatorMemory;

#ifdef _DEBUG
		size_t m_availableBlocks;
#endif // _DEBUG




	};


}