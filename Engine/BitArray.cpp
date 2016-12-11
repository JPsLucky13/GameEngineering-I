#pragma once
#include "BitArray.h"


namespace Engine {

	//Constructor for the bit array
	BitArray::BitArray(size_t i_numBits, bool i_startClear) {
		m_pBits = NULL;
		bitArraySize = 0;
		Create(i_numBits,i_startClear);
	}


	BitArray * BitArray::Create(size_t i_numBits, BlockAllocator * i_pAllocator, bool i_startClear)
	{
		//Store the number of bits
		bitArraySize = i_numBits;

		const size_t bitsPerByte = 8;

#ifdef _WIN64
		m_pBits = new uint64_t[bitArraySize / bitsPerByte];
		assert(m_pBits);
#else
		m_pBits = new uint32_t[bitArraySize / bitsPerByte];
		assert(m_pBits);
#endif


		memset(m_pBits, i_startClear ? 0 : 1, bitArraySize / bitsPerByte);

		return this;
	}

	BitArray * BitArray::Create(size_t i_numBits, bool i_startClear)
	{
		//Store the number of bits
		bitArraySize = i_numBits;

		const size_t bitsPerByte = 8;

#ifdef _WIN64
		m_pBits = new uint64_t[bitArraySize / bitsPerByte];
		assert(m_pBits);
#else
		m_pBits = new uint32_t[bitArraySize / bitsPerByte];
		assert(m_pBits);
#endif


		memset(m_pBits, i_startClear ? 0 : 1, bitArraySize / bitsPerByte);
		return this;
	}

	BitArray::~BitArray()
	{
		_aligned_free(m_pBits);
	}

	void BitArray::ClearAll(void)
	{
		size_t index = 0;

		while (index < bitArraySize)
		{
			m_pBits[index] = 0x00;
			index++;
		}

	}

	void BitArray::SetAll(void)
	{
		size_t index = 0;

		while (index < bitArraySize)
		{
			m_pBits[index] = 0x01;
			index++;
		}

	}

	bool BitArray::AreAllClear(void) const
	{
		size_t index = 0;

		while ((m_pBits[index] == 0x00) && (index < bitArraySize))
		{
			if (m_pBits[index] == 0x01)
				return false;

			index++;
		}

		return true;
	}

	bool BitArray::AreAllSet(void) const
	{
		size_t index = 0;

		while ((m_pBits[index] == 0x01) && (index < bitArraySize))
		{
			if (m_pBits[index] == 0x00)
				return false;

			index++;
		}

		return true;
	}

	inline bool BitArray::IsBitSet(size_t i_bitNumber) const
	{
		return m_pBits[i_bitNumber] == 0x01 ? true : false;
	}

	inline bool BitArray::IsBitClear(size_t i_bitNumber) const
	{
		return m_pBits[i_bitNumber] == 0x00 ? true : false;
	}

	void BitArray::SetBit(size_t i_bitNumber)
	{
		m_pBits[i_bitNumber] = 0x01;
	}

	void BitArray::ClearBit(size_t i_bitNumber)
	{
		m_pBits[i_bitNumber] = 0x00;
	}

	bool BitArray::GetFirstClearBit(size_t & o_bitNumber) const
	{
		size_t index = 0;

		while ((m_pBits[index] == 0x00) && (index < o_bitNumber))
			index++;


		return m_pBits[index] == 0x00 ? true : false;
	}

	bool BitArray::GetFirstSetBit(size_t & o_bitNumber) const
	{
		size_t index = 0;

		while ((m_pBits[index] == 0x01) && (index < o_bitNumber))
			index++;


		return m_pBits[index] == 0x01 ? true : false;
	}

	bool BitArray::operator[](size_t i_index) const
	{
		return m_pBits[i_index] == 0x00 ? false : true;
	}
}