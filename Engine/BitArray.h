#pragma once
#include <stdint.h>
#include "BlockAllocator.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <assert.h> 


namespace Engine {

	class BitArray
	{

	public:

		//Default constructor
		BitArray(size_t i_numBits, bool i_startClear);
		
		BitArray* Create(size_t i_numBits,  BlockAllocator * i_pAllocator, bool i_startClear = true);
		BitArray* Create(size_t i_numBits, bool i_startClear = true);
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


#ifdef _WIN64
		uint64_t * m_pBits;
#else
		uint32_t * m_pBits;
#endif

	};

}