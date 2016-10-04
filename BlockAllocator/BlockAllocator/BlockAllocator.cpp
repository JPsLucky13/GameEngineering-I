#include "BlockAllocator.h"
#include <malloc.h>




//Creates the block allocator and splits it
void BlockAllocator::create(size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	//Get the block of memory and set the size
	startOfMemory = _aligned_malloc(i_sizeMemory, alignment);

	//Split the memory to create a pool of block descriptors
	poolOfBlockDescriptors = ((char*)startOfMemory + i_sizeMemory) - (sizeof(BlockDescriptor) * i_numDescriptors);

	//The list of block descriptors that are not being used
	unusedDescriptors = (BlockDescriptor*)poolOfBlockDescriptors;
	
	BlockDescriptor* head = unusedDescriptors;

	for (int i = 1; i < i_numDescriptors; i++)
	{
		head->m_pNext = unusedDescriptors + i * sizeof(BlockDescriptor);
		head->m_pBlockBase = NULL;
		head->m_sizeBlock = 0;
		head = head->m_pNext;
	}

	head->m_pNext = NULL;
	head->m_pBlockBase = NULL;
	head->m_sizeBlock = 0;

	//Set in place the first bock to be used
	unassignedDescriptors = unusedDescriptors;

	//Set next the following unused block descriptor
	unusedDescriptors = unusedDescriptors->m_pNext;

	//
	unassignedDescriptors->m_pNext = NULL;
	unassignedDescriptors->m_pBlockBase = startOfMemory;
	unassignedDescriptors->m_sizeBlock = i_sizeMemory - (sizeof(BlockDescriptor) * i_numDescriptors);
	
}

void BlockAllocator::destroy()
{
}

void * BlockAllocator::_alloc(size_t i_size)
{

	void * endPtr = unassignedDescriptors + unassignedDescriptors->m_sizeBlock - i_size;

	assignedDescriptors = (BlockDescriptor*)endPtr;
	assignedDescriptors->m_pBlockBase = (char*)endPtr + i_size;
	assignedDescriptors->m_sizeBlock = i_size;
	assignedDescriptors->m_pNext = NULL;

	unassignedDescriptors->m_sizeBlock = unassignedDescriptors->m_sizeBlock - i_size;



	return (void*)unassignedDescriptors;
}

bool BlockAllocator::_free(void * i_ptr)
{
	return false;
}

size_t BlockAllocator::getLargestFreeBlock() const
{
	return size_t();
}

size_t BlockAllocator::getTotalFreeMemory() const
{
	return size_t();
}
