#pragma once


//This class creates the block allocator
class BlockAllocator
{
public:

	struct BlockDescriptor
	{
		void * m_pBlockBase;
		size_t m_sizeBlock;
		BlockDescriptor * m_pNext;
	};


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
private:

	const size_t alignment = 4;
	void * startOfMemory;
	void * pFreeMemoryList;
	void * poolOfBlockDescriptors;
	BlockDescriptor * unusedDescriptors;
	BlockDescriptor * unassignedDescriptors;
	BlockDescriptor * assignedDescriptors;

};
