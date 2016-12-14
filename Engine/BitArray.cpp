#pragma once
#include "BitArray.h"
#include <intrin.h> 


namespace Engine {

	//Constructor for the bit array
	BitArray::BitArray(size_t i_numBits, bool i_startClear) {
		m_pBits = NULL;
		bitArraySize = 0;
		Create(i_numBits,i_startClear);
	}


	BitArray * BitArray::Create(size_t i_numBits, bool i_startClear)
	{
		//Store the number of bits
		bitArraySize = i_numBits;

		
#ifdef _WIN64

		size_t fullBytes = i_numBits / (bitsPerByte * sizeof(uint64_t));
		additionalBits = i_numBits % (bitsPerByte * sizeof(uint64_t));

		sizeOfTheArray = additionalBits == 0 ? fullBytes : fullBytes + 1;

		m_pBits = new uint64_t[sizeOfTheArray];
		assert(m_pBits);

		memset(m_pBits, i_startClear ? 0 : UINT8_MAX, sizeof(uint64_t) * sizeOfTheArray);
#else
		size_t fullBytes = i_numBits / (bitsPerByte * sizeof(uint32_t));
		additionalBits = i_numBits % (bitsPerByte * sizeof(uint32_t));

		sizeOfTheArray = additionalBits == 0 ? fullBytes : fullBytes + 1;

		m_pBits = new uint32_t[sizeOfTheArray];
		assert(m_pBits);

		memset(m_pBits, i_startClear ? 0 : UINT8_MAX, sizeof(uint32_t) * sizeOfTheArray);
#endif

		return this;
	}

	BitArray::~BitArray()
	{
		delete m_pBits;
		m_pBits = NULL;
	}

	void BitArray::ClearAll(void)
	{
#ifdef _WIN64
		memset(m_pBits, 0, sizeof(uint64_t) * sizeOfTheArray);
#else
		memset(m_pBits,0, sizeof(uint32_t) * sizeOfTheArray);

#endif

	}

	void BitArray::SetAll(void)
	{
#ifdef _WIN64
		memset(m_pBits, UINT8_MAX, sizeof(uint64_t) * sizeOfTheArray);
#else
		memset(m_pBits, UINT8_MAX, sizeof(uint32_t) * sizeOfTheArray);

#endif
	}

	bool BitArray::AreAllClear(void) const
	{
		size_t index = 0;
		unsigned long tempIndex;

		//There are no additional bits 
		if (additionalBits == 0)
		{

			while (index < bitArraySize)
			{
				if (!_BIT_SCAN(&tempIndex, m_pBits[index]))
					index++;
				else
					return false;
			}

			return true;

		}

		//There are additional bits
		else
		{

			while (index < bitArraySize)
			{


				if (index != bitArraySize - 1) {

					if (!_BIT_SCAN(&tempIndex, m_pBits[index]))
						index++;
					else
						return false;

				}

				//The last element
				else
				{
					for (size_t i = 0; i < additionalBits; i++)
					{
						if (!IsBitClear((sizeOfTheArray - 1) * (numberOfBits / bitsPerByte) + i))
						{
							return false;
						}


					}

				}
			}
					return true;
		}
	}

	bool BitArray::AreAllSet(void) const
	{
		size_t index = 0;

		//There are no additional bits 
		if (additionalBits == 0)
		{

			while (index < bitArraySize)
			{
				if (m_pBits[index] == _MAX_VALUE)
					index++;
				else
					return false;
			}

			return true;

		}

		//There are additional bits
		else
		{

			while (index < bitArraySize)
			{


				if(index != bitArraySize -1){

				if (m_pBits[index] == _MAX_VALUE)
					index++;
				else
					return false;

				}

				//The last element
				else
				{
					for (size_t i = 0; i < additionalBits; i++)
					{
						if (!IsBitSet((sizeOfTheArray - 1) * (numberOfBits / bitsPerByte) + i))
						{
							return false;
						}


					}

				}
			}
					return true;
		}
	}

	inline bool BitArray::IsBitSet(size_t i_bitNumber) const
	{
		size_t element = i_bitNumber / numberOfBits;
		return (m_pBits[element]  & (bitShift << (i_bitNumber % numberOfBits))) ? true : false;

	}

	inline bool BitArray::IsBitClear(size_t i_bitNumber) const
	{

		size_t element = i_bitNumber / numberOfBits;
		return (m_pBits[element] & (bitShift << (i_bitNumber % numberOfBits))) ? false : true;
	}

	void BitArray::SetBit(size_t i_bitNumber)
	{
		size_t element = i_bitNumber / numberOfBits;
		m_pBits[element] |= bitShift << (i_bitNumber % numberOfBits);
	}

	void BitArray::ClearBit(size_t i_bitNumber)
	{
		//Find the element in m_pBits
		size_t element = i_bitNumber / numberOfBits;
		m_pBits[element] &= ~(bitShift << (i_bitNumber % numberOfBits));
	}

	bool BitArray::GetFirstClearBit(size_t & o_bitNumber) const
	{
		//There are no additional bits 
		if (additionalBits == 0)
		{
			//Look for the bit that is set to 1
			for (size_t i = 0; i < sizeOfTheArray; i++)
			{
				if (m_pBits[i] != _MAX_VALUE)
				{

					for (size_t j = 0; j < numberOfBits; j++) {

						if (IsBitClear(i * numberOfBits + j))
						{
							o_bitNumber = i * numberOfBits + j;
							return true;
						}


					}
				}
			}

			return false;

		}

		//There are additional bits
		else
		{

			//Look for the bit that is set to 1
			for (size_t i = 0; i < sizeOfTheArray - 1; i++)
			{
				if (m_pBits[i] != _MAX_VALUE)
				{

					for (size_t j = 0; j < numberOfBits; j++) {

						if (IsBitClear(i * numberOfBits + j))
						{
							o_bitNumber = i * numberOfBits + j;
							return true;
						}


					}
				}
			}


			for (size_t i = 0; i < additionalBits; i++) {

				if (IsBitClear((sizeOfTheArray - 1) * numberOfBits  + i))
				{
					o_bitNumber = (sizeOfTheArray - 1) * numberOfBits + i;
					return true;
				}


			}

			return false;

		}
	}

	bool BitArray::GetFirstSetBit(size_t & o_bitNumber) const
	{
		unsigned long tempIndex;

		//There are no additional bits 
		if (additionalBits == 0)
		{
					//Look for the bit that is set to 1
					for (size_t i = 0; i < sizeOfTheArray; i++)
					{
						if (_BIT_SCAN(&tempIndex, m_pBits[i]))
						{
							o_bitNumber = i * (numberOfBits/bitsPerByte) + tempIndex;
							return true;
						}
					}

					return false;

		}

		//There are additional bits
		else
		{

			//Look for the bit that is set to 1
			for (size_t i = 0; i < sizeOfTheArray - 1; i++)
			{
				if (_BIT_SCAN(&tempIndex, m_pBits[i]))
				{
					o_bitNumber = i * (numberOfBits / bitsPerByte) + tempIndex;
					return true;
				}
			}

			for (size_t i = 0; i < additionalBits; i++) {
				
				if (IsBitSet((sizeOfTheArray - 1) * (numberOfBits / bitsPerByte) + i))
				{
					o_bitNumber = (sizeOfTheArray - 1) * (numberOfBits / bitsPerByte) + i;
					return true;
				}
			

			}

			return false;

		}
	}

	bool BitArray::operator[](size_t i_index) const
	{
		return m_pBits[i_index] == 0 ? false : true;
	}
}