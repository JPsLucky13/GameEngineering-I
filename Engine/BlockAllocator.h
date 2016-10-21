#pragma once
#pragma once
#include <stdio.h>
namespace Engine {
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
		//FOr testing
		int k = 0;

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

		//contains
		bool _contains(void* pointer) const;

		//isAllocator Adjacent
		bool _isAllocated(void* pointer)const;

		size_t getLargestFreeBlock() const;
		size_t getTotalFreeMemory() const;
		void PrintBlockDescriptors();

		//Getters
		BlockDescriptor * unusedDescriptorsHeadGetter() { return unusedDescriptorsHead; }
		BlockDescriptor * freeDescriptorsHeadGetter() { return freeDescriptorsHead; }
		BlockDescriptor * outstandingDescriptorsHeadGetter() { return outstandingDescriptorsHead; }

		


	private:
		void BlockAllocator::InitializeUnusedDescriptors(size_t i_sizeMemory, unsigned int i_numDescriptors);
		void BlockAllocator::SelectionSortBlockDescriptorPointer(BlockDescriptor * bd_pointer);
		void BlockAllocator::SwapBlockDescriptorInfo(BlockDescriptor * lhs_bd_pointer, BlockDescriptor * rhs_bd_pointer);
		void BlockAllocator::GarabageCollector();
	private:
		const size_t minimumSize = 12;
		const size_t alignment = 4;
		void * startOfMemory;
		void * endOfRightSideOfMemory;
		BlockDescriptor * unusedDescriptorsHead;
		BlockDescriptor * freeDescriptorsHead;
		BlockDescriptor * outstandingDescriptorsHead;
		int totalBlockDescriptors;


	};
}