#include "StringPool.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "Debug.h"
namespace Engine {
	StringPool::StringPool() :
		m_pStartBuffer(NULL),
		m_pEndStrings(NULL),
		m_pEndBuffer(NULL),
		m_pBlockAllocator(NULL)
		{};


	StringPool * StringPool::create(size_t i_bytesInPool, BlockAllocator * i_pBlockAllocator)
{
	//Create the block
	m_pStartBuffer = reinterpret_cast<uint8_t *>(i_pBlockAllocator->_alloc(i_bytesInPool));

	//Construct the string pool
	StringPool * m_stringPool = new StringPool(m_pStartBuffer, i_bytesInPool);

	return m_stringPool;
}

StringPool::StringPool(uint8_t * i_pPool, size_t i_bytes) :
	m_pStartBuffer(i_pPool),
	m_pEndStrings(m_pStartBuffer),
	m_pEndBuffer(m_pStartBuffer + i_bytes)
{};

StringPool::~StringPool()
{
	m_pBlockAllocator->_free(m_pStartBuffer);
}

const char * StringPool::add(const char * i_pString)
{
	size_t stringSize = strlen(i_pString);
	size_t * p_StringSize = reinterpret_cast<size_t *>(m_pEndStrings);
	p_StringSize++;
	char * targetCharacter = reinterpret_cast<char *>(p_StringSize);
	targetCharacter += stringSize + 1;
	uint8_t * comparer = reinterpret_cast<uint8_t*>(targetCharacter);

	//Check if memory is available
	if (m_pEndStrings == m_pEndBuffer || comparer > m_pEndBuffer)
	{
		DEBUG_LOG_OUTPUT("Not more memory is available");
		return nullptr;
	}

	//pointer to traver the string pool
	char * traversalPointer = reinterpret_cast<char*>(m_pEndStrings);

	//Check if the start and end pointer are at the same location
	//Pool is empty
	if (m_pEndStrings == m_pStartBuffer)
	{
		
		//pointer to traver the string pool
		char * traversalPointer = reinterpret_cast<char*>(m_pEndStrings);

		size_t stringSize = strlen(i_pString);
		size_t * traversalCopy = reinterpret_cast<size_t *>(traversalPointer);
		*traversalCopy = stringSize;
		traversalCopy++;
		traversalPointer = reinterpret_cast<char*>(traversalCopy);
		strcpy_s(traversalPointer, stringSize+1,i_pString);
		m_pEndStrings = reinterpret_cast<uint8_t *>(traversalPointer + stringSize +1);

		return traversalPointer;

	}


	else {
	
		//Find the string
		const char * result = find(i_pString);
	
		if (result)
		{
			return result;
		}
		else {
			//pointer to traverse the string pool
			char * traversalPointer = reinterpret_cast<char*>(m_pEndStrings);

			size_t stringSize = strlen(i_pString);
			size_t * traversalCopy = reinterpret_cast<size_t *>(traversalPointer);
			*traversalCopy = stringSize;
			traversalCopy++;
			traversalPointer = reinterpret_cast<char*>(traversalCopy);
			strcpy_s(traversalPointer, stringSize +1, i_pString);
			m_pEndStrings = reinterpret_cast<uint8_t *>(traversalPointer + stringSize + 1);

			return traversalPointer;

		}


	}
}

const char * StringPool::find(const char * i_pString)
{

	//pointer to traver the string pool
	char * traversalPointer = reinterpret_cast<char*>(m_pStartBuffer);
	size_t * traversalCopy = reinterpret_cast<size_t *>(traversalPointer);
	size_t * endOfStrings = reinterpret_cast<size_t *>(m_pEndStrings);

	//size of the string to compare
	size_t stringSize = strlen(i_pString);
	
	while (traversalCopy != endOfStrings)
	{


		//First check the size
		if (stringSize != *traversalCopy)
		{
			//Move the pointer
			size_t numberOfCharacters = *traversalCopy;
			traversalCopy++;
			traversalPointer = reinterpret_cast<char*>(traversalCopy);
			traversalPointer += numberOfCharacters + 1;
			traversalCopy = reinterpret_cast<size_t *>(traversalPointer);
			
		}
		else
		{
			//Compare the contents of the string
			size_t numberOfCharacters = *traversalCopy;
			traversalCopy++;
			traversalPointer = reinterpret_cast<char*>(traversalCopy);
			
			//The strings are equal
			if (strcmp(traversalPointer, i_pString) == 0)
			{
				return traversalPointer;
			}
			else {
				traversalPointer += numberOfCharacters +1;
				traversalCopy = reinterpret_cast<size_t *>(traversalPointer);
			}
		}
	}
	return nullptr;
}


}

