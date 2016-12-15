#pragma once
#include <stdint.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <assert.h> 
#include "BlockAllocator.h"

#ifdef _WIN64
#define _MAX_VALUE UINT64_MAX
#define _BIT_SCAN(index, mask) _BitScanForward64(index,mask) 
#else
#define _MAX_VALUE UINT32_MAX
#define _BIT_SCAN(index, mask) _BitScanForward(index,mask) 
#endif

namespace Engine {

	class BitArray
	{

	public:

		//Default constructor
		BitArray(size_t i_numBits,bool i_startClear);
		BitArray(size_t i_numBits,BlockAllocator * i_BlockAllocator, bool i_startClear);
	
		BitArray* Create(size_t i_numBits,bool i_startClear = true);
		BitArray* Create(size_t i_numBits, BlockAllocator * i_BlockAllocator, bool i_startClear = true);
		~BitArray();

		void ClearAll(void);
		void SetAll(void);

		bool AreAllClear(void) const;
		bool AreAllSet(void)const;

		inline bool IsBitSet(size_t i_bitNumber) const;
		inline bool IsBitClear(size_t i_bitNumber)const;

		void SetBit(size_t i_bitNumber);
		void ClearBit(size_t i_bitNumber);

		bool GetFirstClearBit(size_t & o_bitNumber)const;
		bool GetFirstSetBit(size_t & o_bitNumber) const;

		bool operator[](size_t i_index)const;





	private:

		size_t bitArraySize = 0;
		const size_t bitsPerByte = 8;
		size_t sizeOfTheArray = 0;

		//Bits that do not fit into the defined m_pBits pointer size
		size_t additionalBits;

#ifdef _WIN64
		uint64_t * m_pBits;
		const size_t numberOfBits = 64;
		const uint64_t bitShift = 1;
#else
		uint32_t * m_pBits;
		const size_t numberOfBits = 32;
		const uint32_t bitShift = 1;
#endif

	};

}