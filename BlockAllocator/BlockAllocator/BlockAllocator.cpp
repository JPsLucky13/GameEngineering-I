#include "BlockAllocator.h"
#include <malloc.h>

//Constructor for the block allocator
BlockAllocator::BlockAllocator() {
	unusedDescriptorsHead = NULL;
	freeDescriptorsHead = NULL;
	outstandingDescriptorsHead = NULL;
	startOfMemory = NULL;
	totalBlockDescriptors = 0;
}

//Creates the block allocator and splits it
void BlockAllocator::create(size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	//Get the block of memory and set the size
	startOfMemory = _aligned_malloc(i_sizeMemory, alignment);

	InitializeUnusedDescriptors(i_sizeMemory,i_numDescriptors);

	//Set in place the first bock to be used
	freeDescriptorsHead = unusedDescriptorsHead;

	//Set next the following unused block descriptor
	unusedDescriptorsHead = unusedDescriptorsHead->m_pNext;

	
	freeDescriptorsHead->m_pNext = NULL;
	freeDescriptorsHead->m_pBlockBase = startOfMemory;
	freeDescriptorsHead->m_sizeBlock = i_sizeMemory - (sizeof(BlockDescriptor) * i_numDescriptors);
}

void BlockAllocator::destroy()
{
}

void * BlockAllocator::_alloc(size_t i_size)
{


	//Check that there are unused block descriptors and the amount of memory available is greater than what is requested
	if(unusedDescriptorsHead != NULL && getLargestFreeBlock() >= i_size)
	{ 

	void * endPtr = (char*)freeDescriptorsHead->m_pBlockBase + freeDescriptorsHead->m_sizeBlock - i_size;
	

	BlockDescriptor* ptr = unusedDescriptorsHead;
	unusedDescriptorsHead = unusedDescriptorsHead->m_pNext;

	ptr->m_pBlockBase = endPtr;
	ptr->m_sizeBlock = i_size;

	
	ptr->m_pNext = outstandingDescriptorsHead;
	outstandingDescriptorsHead = ptr;
	

	freeDescriptorsHead->m_sizeBlock = freeDescriptorsHead->m_sizeBlock - i_size;

	return endPtr;

	}

	//There are no more unused block descriptors
	else
	{

		return NULL;

	}



}

bool BlockAllocator::_free(void * i_ptr)
{
	return false;
}

size_t BlockAllocator::getLargestFreeBlock() const
{
	//Iterate throught the linked list of free blocks to check which is the largest
	size_t largestSize = 0;
	for (BlockDescriptor * ptr = freeDescriptorsHead; ptr != NULL; ptr = ptr->m_pNext)
	{
		if (largestSize < ptr->m_sizeBlock) {
			largestSize = ptr->m_sizeBlock;
		}
	}
	return largestSize;
}

size_t BlockAllocator::getTotalFreeMemory() const
{
	//Iterate through the list of free memory blocks and add the memory to get the total memory amount
	size_t total = 0;
	for (BlockDescriptor * ptr = freeDescriptorsHead; ptr != NULL; ptr = ptr->m_pNext)
	{
		total += ptr->m_sizeBlock;
	}

	return total;
}

void BlockAllocator::PrintBlockDescriptors()
{
	//Print the heading of the block allocator
	printf("Block allocator: Total free memory %d, Lagest Free Block %d, number of Block descriptors %d\n", getTotalFreeMemory(),getLargestFreeBlock(), totalBlockDescriptors);
	printf("-------------------------------------------------------------------------------------------\n");
	printf("---------------------------Unused Block Descriptors------------------------------\n");

	
	//Print the list of unused block allocators with their ID and Block Size
	for (BlockDescriptor * ptr = unusedDescriptorsHead; ptr != NULL; ptr = ptr->m_pNext)
	{
		printf("BD: id = %d, Block_size = %d\n", ptr->m_id, ptr->m_sizeBlock);
	}

	printf("-------------------------------------------------------------------------------------------\n");
	printf("---------------------------Free Block Descriptors------------------------------\n");

	//Print the list of free block allocators with their ID and Block Size
	for (BlockDescriptor * ptr = freeDescriptorsHead; ptr != NULL; ptr = ptr->m_pNext)
	{
		printf("BD: id = %d, Block_size = %d\n", ptr->m_id, ptr->m_sizeBlock);
	}

	printf("-------------------------------------------------------------------------------------------\n");
	printf("---------------------------Outstanding Block Descriptors------------------------------\n");

	//Print the list of free block allocators with their ID and Block Size
	for (BlockDescriptor * ptr = outstandingDescriptorsHead; ptr != NULL; ptr = ptr->m_pNext)
	{
		printf("BD: id = %d, Block_size = %d\n", ptr->m_id, ptr->m_sizeBlock);
	}

	printf("-------------------------------------------------------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------\n");
	
}

void BlockAllocator::InitializeUnusedDescriptors(size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	totalBlockDescriptors = i_numDescriptors;

	//Split the memory to create a pool of block descriptors
	char *poolOfBlockDescriptors = ((char*)startOfMemory + i_sizeMemory) - (sizeof(BlockDescriptor) * i_numDescriptors);

	for (int i = 0; i < i_numDescriptors; i++)
	{
		BlockDescriptor* newDescriptor = (BlockDescriptor*)poolOfBlockDescriptors + i;
		newDescriptor->m_pBlockBase = NULL;
		newDescriptor->m_sizeBlock = 0;

		#if _DEBUG
		newDescriptor->m_id = totalBlockDescriptors;
		#endif // DEBUG

		totalBlockDescriptors--;
		newDescriptor->m_pNext = unusedDescriptorsHead;
		unusedDescriptorsHead = newDescriptor;
		
	}


}
