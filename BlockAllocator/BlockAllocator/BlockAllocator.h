#pragma once
#include <stdio.h>

#ifdef _DEBUG
#define DEBUG_LOG_DESCRIPTORS(fmt,...) PrintBlockDescriptors()
#define DEBUG_LOG_OPERATION(fmt,...) PrintOperation()
#else
#define DEBUG_LOG_DESCRIPTORS(fmt,...) void(0)
#define DEBUG_LOG_OPERATION(fmt,...) void(0)
#endif // DEBUG

//This class creates the block allocator
class BlockAllocator
{
public:

	struct BlockDescriptor
	{
		void * m_pBlockBase;
		size_t m_sizeBlock;
		BlockDescriptor * m_pNext;

		//Keep track of the ids of the block descriptors
		#ifdef _DEBUG
		unsigned int m_id = 0;
		#endif//DEBUG
	};

	//Constructor
	BlockAllocator();

	//Create a new block allocator
	void create(size_t i_sizeMemory, unsigned int i_numDescriptors);
	//Destroys the block allocator
	void destroy();

	//Allocate
	void * _alloc(size_t i_size);

	//free
	bool _free(void * i_ptr);

	size_t getLargestFreeBlock() const;
	size_t getTotalFreeMemory() const;
	void PrintBlockDescriptors();

private:
	void BlockAllocator::InitializeUnusedDescriptors(size_t i_sizeMemory, unsigned int i_numDescriptors);

private:

	const size_t alignment = 4;
	void * startOfMemory;
	BlockDescriptor * unusedDescriptorsHead;
	BlockDescriptor * freeDescriptorsHead;
	BlockDescriptor * outstandingDescriptorsHead;
	int totalBlockDescriptors;


};
