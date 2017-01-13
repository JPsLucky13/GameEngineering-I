#pragma once
#include "NewDelete.h"



//To set a static pointer to the block allocator
Engine::BlockAllocator * GetBlockAllocator(Engine::BlockAllocator * blockAllocator) {
	static Engine::BlockAllocator * blockAllocatorRef = blockAllocator;
	
	return blockAllocatorRef;
}

//To set a static pointer to the FSAManager
Engine::FSAManager * GetFSAManager(Engine::FSAManager * i_fsaManager)
{
	static Engine::FSAManager * fsaManagerRef = i_fsaManager;

	return fsaManagerRef;
	
}

Engine::FixedBlockAllocator * FindFixedSizeAllocator(size_t i_size) {

	for (size_t i = 0; i < GetFSAManager(nullptr)->GetNumFSAs(); i++)
	{
		if (GetFSAManager(nullptr)->FSASizes[i].sizeBlock >= i_size)
		{
			return GetFSAManager(nullptr)->fixedBlockAllocatorsAvailable[i];
		}
	}

	return NULL;
	

}


void * operator new(size_t i_size)
{
	DEBUG_LOG_MESSAGE("Calling new(size_t) with (%zx).\n", i_size);

	//Verify the bytes the user is requesting to determine if an allocation is needed on the Block Allocator or the FSA
	void * pReturn = nullptr;

	Engine::FixedBlockAllocator * pFSA = FindFixedSizeAllocator(i_size);

	if (pFSA)
	{
		//Verify the Fsa has available blocks
		if(!pFSA->GetBitArray()->AreAllClear())
		pReturn = pFSA->_alloc(i_size);

		else 
		pReturn = GetBlockAllocator(nullptr)->_alloc(i_size);

	}

	//if no Fsa was found or there was one and it is full
	if (pReturn == nullptr)
		pReturn = GetBlockAllocator(nullptr)->_alloc(i_size);

	return pReturn;

}


void operator delete(void * ptr)
{
	bool freeFSA = false;

	DEBUG_LOG_MESSAGE("Calling delete(void *) with (%zx).\n", ptr);
	
	//Check if the pointer is in the range of a FSA
	for (size_t i = 0; i < GetFSAManager(nullptr)->GetNumFSAs(); i++)
	{
		if (GetFSAManager(nullptr)->fixedBlockAllocatorsAvailable[i]->isValidPointer(ptr))
		{
			GetFSAManager(nullptr)->fixedBlockAllocatorsAvailable[i]->_free(ptr);
			freeFSA = true;
		}
	}

	//Pointer was not in a FSA
	if(!freeFSA)
	GetBlockAllocator(nullptr)->_free(ptr);
}

void * operator new(size_t i_size, Engine::BlockAllocator * i_BlockAllocator) {

	DEBUG_LOG_MESSAGE("Calling new(void *) with (%zx).\n");

	return i_BlockAllocator->_alloc(i_size);
}

void operator delete(void * ptr, Engine::BlockAllocator * i_BlockAllocator) {
	i_BlockAllocator->_free(ptr);
}


void * operator new(size_t i_size ,const char * file, const char * func, const unsigned int line)
{
	DEBUG_LOG_MESSAGE("Calling new(size_t,const char*,const char*,const unsigned int)\n Size: %zu\n File: %s\n Func: %s\n Line: %d\n ) with (%zx).\n", i_size,file,func,line);

	//Verify the bytes the user is requesting to determine if an allocation is needed on the Block Allocator or the FSA
	void * pReturn = nullptr;

	Engine::FixedBlockAllocator * pFSA = FindFixedSizeAllocator(i_size);

	if (pFSA)
	{
		//Verify the Fsa has available blocks
		if (!pFSA->GetBitArray()->AreAllClear())
			pReturn = pFSA->_alloc(i_size);

		else
			pReturn = GetBlockAllocator(nullptr)->_alloc(i_size);

	}

	//if no Fsa was found or there was one and it is full
	if (pReturn == nullptr)
		pReturn = GetBlockAllocator(nullptr)->_alloc(i_size);

	return pReturn;

}

void operator delete(void * ptr, const char * file, const char * func, const unsigned int line)
{
	bool freeFSA = false;

	DEBUG_LOG_MESSAGE("Calling delete(size_t,const char*,const char*,const unsigned int)\n Size: %zu\n File: %s\n Func: %s\n Line: %d\n ) with (%zx).\n", ptr, file, func, line);

	//Check if the pointer is in the range of a FSA
	for (size_t i = 0; i < GetFSAManager(nullptr)->GetNumFSAs(); i++)
	{
		if (GetFSAManager(nullptr)->fixedBlockAllocatorsAvailable[i]->isValidPointer(ptr))
		{
			GetFSAManager(nullptr)->fixedBlockAllocatorsAvailable[i]->_free(ptr);
			freeFSA = true;
		}
	}

	//Pointer was not in a FSA
	if (!freeFSA)
		GetBlockAllocator(nullptr)->_free(ptr);
}

void * operator new[](size_t i_size)
{
	DEBUG_LOG_MESSAGE("Calling new(size_t) with (%zx).\n", i_size);

	//Verify the bytes the user is requesting to determine if an allocation is needed on the Block Allocator or the FSA
	void * pReturn = nullptr;

	Engine::FixedBlockAllocator * pFSA = FindFixedSizeAllocator(i_size);

	if (pFSA)
	{
		//Verify the Fsa has available blocks
		if (!pFSA->GetBitArray()->AreAllClear())
			pReturn = pFSA->_alloc(i_size);

		else
			pReturn = GetBlockAllocator(nullptr)->_alloc(i_size);

	}

	//if no Fsa was found or there was one and it is full
	if (pReturn == nullptr)
		pReturn = GetBlockAllocator(nullptr)->_alloc(i_size);

	return pReturn;

}

void operator delete[](void * ptr)
{
	bool freeFSA = false;

	DEBUG_LOG_MESSAGE("Calling delete(void *) with (%zx).\n", ptr);

	//Check if the pointer is in the range of a FSA
	for (size_t i = 0; i < GetFSAManager(nullptr)->GetNumFSAs(); i++)
	{
		if (GetFSAManager(nullptr)->fixedBlockAllocatorsAvailable[i]->isValidPointer(ptr))
		{
			GetFSAManager(nullptr)->fixedBlockAllocatorsAvailable[i]->_free(ptr);
			freeFSA = true;
		}
	}

	//Pointer was not in a FSA
	if (!freeFSA)
		GetBlockAllocator(nullptr)->_free(ptr);

}


