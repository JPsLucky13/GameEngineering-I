#pragma once
#pragma once
#include <stdio.h>
#include <stdint.h>
#include "Debug.h"
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
		void* tempPtr;
		struct BlockDescriptor
		{
			void * m_pBlockBase;
			size_t m_sizeBlock;
			BlockDescriptor * m_pNext;

			//Keep track of the ids of the block descriptors
#ifdef _DEBUG
			size_t m_id = 0;
#endif//DEBUG
		};

		//Constructor
		BlockAllocator();

		//Create a new block allocator
		void create(const size_t i_sizeMemory,const unsigned int i_numDescriptors);
		//Destroys the block allocator
		void destroy();

		//Allocate
		void * _alloc(const size_t i_size, const uint8_t alignment);
		void * _alloc(const size_t i_size);

		//free
		bool _free(const void * i_ptr);

		//contains
		inline bool _contains(const void* pointer) const;

		//isAllocator Adjacent
		bool _isAllocated(const void* pointer)const;

		BlockAllocator * SetBlockAllocator(BlockAllocator * BlockAllocatorReference) { ; }




		size_t getLargestFreeBlock() const;
		size_t getTotalFreeMemory() const;

#ifdef _DEBUG
		void PrintBlockDescriptors() const;
#endif//DEBUG

		inline BlockDescriptor * unusedDescriptorsHeadGetter() const;
		inline BlockDescriptor * freeDescriptorsHeadGetter() const;
		inline BlockDescriptor * outstandingDescriptorsHeadGetter() const;

		
		void BlockAllocator::GarabageCollector();

	private:
		void BlockAllocator::InitializeUnusedDescriptors(const size_t i_sizeMemory, const size_t i_numDescriptors);
		void BlockAllocator::SelectionSortBlockDescriptorPointer(BlockDescriptor *  const bd_pointer);
		void BlockAllocator::SwapBlockDescriptorInfo(BlockDescriptor * lhs_bd_pointer, BlockDescriptor * rhs_bd_pointer);
		void BlockAllocator::SortFreeBlockListByAddress(BlockDescriptor * const bd_pointer);

	private:
		const size_t minimumSize = 8;
		const size_t alignment = 4;




#ifdef _DEBUG

		
		

		const size_t guardBandSize = 4;
#else
		
		const size_t guardBandSize = 0;
#endif
		const int arrobaCharacter = 64;
		const int guardBandCharacter = 71;
		uint8_t * startOfMemory;
		void * endOfRightSideOfMemory;
		BlockDescriptor * unusedDescriptorsHead;
		BlockDescriptor * freeDescriptorsHead;
		BlockDescriptor * outstandingDescriptorsHead;
		size_t totalBlockDescriptors;


	};







}

#include "BlockAllocator-inl.h"