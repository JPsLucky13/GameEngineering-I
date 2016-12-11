#include <assert.h>
#include <algorithm>
#include <vector>
#include "BlockAllocator.h"

#define __TRACK_ALLOCATIONS

//#define TEST_SINGLE_LARGE_ALLOCATION

bool HeapManager_UnitTest()
{

	const size_t 		sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 2048;

	// Allocate memory for my test heap.
	void * pHeapMemory = _aligned_malloc(sizeHeap, 4);
	assert(pHeapMemory);

	// Create a heap manager for my test heap.
	Engine::BlockAllocator pHeapManager; 
	pHeapManager.create(sizeHeap, numDescriptors);
	

#ifdef TEST_SINGLE_LARGE_ALLOCATION
	// This is a test I wrote to check to see if using the whole block if it was almost consumed by 
	// an allocation worked. Also helped test my ShowFreeBlocks() and ShowOutstandingAllocations().
	{
		pHeapManager.PrintBlockDescriptors();

		size_t largestBeforeAlloc = pHeapManager.getLargestFreeBlock();
		//void * pPtr = alloc(pHeapManager, largestBeforeAlloc - HeapManager::s_MinumumToLeave);

		void * pPtr =  pHeapManager._alloc(largestBeforeAlloc);

		if (pPtr)
		{
			pHeapManager.PrintBlockDescriptors();
			printf("\n");
#ifdef __TRACK_ALLOCATIONS
			pHeapManager.PrintBlockDescriptors();
#endif // __TRACK_ALLOCATIONS
			printf("\n");

			size_t largestAfterAlloc = pHeapManager.getLargestFreeBlock();
			pHeapManager._free(pPtr);

			pHeapManager.PrintBlockDescriptors();
#ifdef __TRACK_ALLOCATIONS
			pHeapManager.PrintBlockDescriptors();
#endif // __TRACK_ALLOCATIONS
			printf("\n");

			pHeapManager.GarabageCollector();

			pHeapManager.PrintBlockDescriptors();
#ifdef __TRACK_ALLOCATIONS
			pHeapManager.PrintBlockDescriptors();
#endif // __TRACK_ALLOCATIONS
			printf("\n");

			size_t largestAfterCollect = pHeapManager.getLargestFreeBlock();
		}
	}
#endif

	std::vector<void *> AllocatedAddresses;

	long	numAllocs = 0;
	long	numFrees = 0;
	long	numCollects = 0;

	bool	done = false;

	// allocate memory of random sizes up to 1024 bytes from the heap manager
	// until it runs out of memory
	do
	{
		const size_t		maxTestAllocationSize = 1024;

		//const unsigned int	alignments[] = { 4, 4, 4, 4, 4 };

		const unsigned int	alignments[] = { 4, 8, 16, 32, 64 };

		unsigned int	index = rand() % (sizeof(alignments) / sizeof(alignments[0]));

		unsigned int	alignment = alignments[index];

		size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));

		void * pPtr = pHeapManager._alloc(sizeAlloc,alignment);

		assert((reinterpret_cast<uintptr_t>(pPtr) & (alignment - 1)) == 0);

		if (pPtr == NULL)
		{
			pHeapManager.GarabageCollector();

			pPtr = pHeapManager._alloc(sizeAlloc, alignment);

			if (pPtr == NULL)
			{
				done = true;
				break;
			}
		}



		AllocatedAddresses.push_back(pPtr);
		numAllocs++;

		const unsigned int freeAboutEvery = 10;
		const unsigned int garbageCollectAboutEvery = 40;

		if (!AllocatedAddresses.empty() && ((rand() % freeAboutEvery) == 0))
		{
			void * pPtr = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			bool success = pHeapManager._free(pPtr);			
			assert(success);

			numFrees++;
		}

		if ((rand() % garbageCollectAboutEvery) == 0)
		{
			pHeapManager.GarabageCollector();
			
			numCollects++;
		}

	} while (1);

	printf("After exhausting allocations:\n");

#ifdef _DEBUG
	pHeapManager.PrintBlockDescriptors();
#endif // __TRACK_ALLOCATIONS

	printf("\n");
	if (std::find(AllocatedAddresses.begin(), AllocatedAddresses.end(), pHeapManager.tempPtr) != AllocatedAddresses.end()) {
		int a = 0;
	}
	// now free those blocks in a random order
	if (!AllocatedAddresses.empty())
	{
		// randomize the addresses
		std::random_shuffle(AllocatedAddresses.begin(), AllocatedAddresses.end());

		// return them back to the heap manager
		while (!AllocatedAddresses.empty())
		{
			void * pPtr = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			bool success = pHeapManager._contains(pPtr);
			assert(success);

			success = pHeapManager._isAllocated(pPtr);
			assert(success);

			success = pHeapManager._free(pPtr);
			assert(success);
		}

		printf("After freeing allocations:\n");

#ifdef _DEBUG
		pHeapManager.PrintBlockDescriptors();
#endif // __TRACK_ALLOCATIONS

		// do garbage collection
		pHeapManager.GarabageCollector();
		// our heap should be one single block, all the memory it started with

		printf("After garbage collection:\n");

#ifdef _DEBUG
		pHeapManager.PrintBlockDescriptors();
#endif // __TRACK_ALLOCATIONS

		printf("\n");		// do a large test allocation to see if garbage collection worked
		void * pPtr = pHeapManager._alloc(sizeHeap / 2, 4);
		assert(pPtr);

		if (pPtr)
		{
			bool success = pHeapManager._free(pPtr);
			assert(success);

		}
	}

	pHeapManager.destroy();


	_aligned_free(pHeapMemory);

	// we succeeded
	return true;
}