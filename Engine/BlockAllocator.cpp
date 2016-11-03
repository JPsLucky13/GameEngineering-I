#include "BlockAllocator.h"
#include <malloc.h>
#include <string.h>

namespace Engine {
	//Constructor for the block allocator
	BlockAllocator::BlockAllocator() {
		unusedDescriptorsHead = NULL;
		freeDescriptorsHead = NULL;
		outstandingDescriptorsHead = NULL;
		startOfMemory = NULL;
		totalBlockDescriptors = 0;
	}

	//Creates the block allocator and splits it
	void BlockAllocator::create(const size_t i_sizeMemory,const unsigned int i_numDescriptors)
	{
		//Get the block of memory and set the size
		startOfMemory = reinterpret_cast<unsigned char*>(_aligned_malloc(i_sizeMemory, alignment));
		memset(startOfMemory, 64, i_sizeMemory);

		InitializeUnusedDescriptors(i_sizeMemory, i_numDescriptors);

		//Set in place the first bock to be used
		freeDescriptorsHead = unusedDescriptorsHead;

		//Set next the following unused block descriptor
		unusedDescriptorsHead = unusedDescriptorsHead->m_pNext;


		freeDescriptorsHead->m_pNext = NULL;
		freeDescriptorsHead->m_pBlockBase = startOfMemory;
		freeDescriptorsHead->m_sizeBlock = i_sizeMemory - (sizeof(BlockDescriptor) * i_numDescriptors);

		endOfRightSideOfMemory = startOfMemory + (i_sizeMemory - (sizeof(BlockDescriptor) * i_numDescriptors));
	}

	void BlockAllocator::destroy()
	{
		_aligned_free(startOfMemory);
	}

	void * BlockAllocator::_alloc(const size_t i_size)
	{
		
#ifdef _DEBUG
		//Extra size allocate for the user to support guardbands
		size_t guardBand = i_size + 12;
#else
		size_t guardBand = i_size;
#endif

		void * basePtr;

		//The index to get to the selected free block descriptor
		int selectedIndex = 0;

		if (getLargestFreeBlock() >= i_size)
		{

			//Sort bi size the free block descriptor linked list.
			SelectionSortBlockDescriptorPointer(freeDescriptorsHead);

			//Block descriptor to cycle through the free list to find the selected free block descriptor
			BlockDescriptor * tempSelected = freeDescriptorsHead;

			//Block descriptor to find the previous block descriptor to sleected to link it to the next of the selected one
			BlockDescriptor * tempPrevSelected = freeDescriptorsHead;




			//Cyle throught the free list until the size of the current block is appropriate
			while (tempSelected->m_sizeBlock < guardBand)
			{

				selectedIndex++;
				tempSelected = tempSelected->m_pNext;
			}

			//Traverse to the previous block descriptor to the selected one
			for (int i = 0;i < selectedIndex-1;i++)
			{
				tempPrevSelected = tempPrevSelected->m_pNext;

			}


			//Give the user the entire block
			if (tempSelected->m_sizeBlock < guardBand + minimumSize)
			{

				//The selected element is the head of the free list
				if (tempPrevSelected == tempSelected)
				{
					freeDescriptorsHead = tempSelected->m_pNext;

				}

				//Guard Banding




					tempPrevSelected->m_pNext = tempSelected->m_pNext;
					tempSelected->m_pNext = outstandingDescriptorsHead;
					outstandingDescriptorsHead = tempSelected;

				//Pointer to return to the user
				basePtr = tempSelected->m_pBlockBase;
			}

			//Divide the block
			else {
				
				if (unusedDescriptorsHead != NULL)
				{

					//Assign an unused block descriptor the memory the user requested
					BlockDescriptor* ptr = unusedDescriptorsHead;
					unusedDescriptorsHead = unusedDescriptorsHead->m_pNext;

					ptr->m_pBlockBase = reinterpret_cast<unsigned char*>(tempSelected->m_pBlockBase) + (tempSelected->m_sizeBlock - i_size);
					ptr->m_sizeBlock = i_size;

					ptr->m_pNext = outstandingDescriptorsHead;
					outstandingDescriptorsHead = ptr;

					//Reduce the size of the free block that stays in the list
					tempSelected->m_sizeBlock -= i_size;

					//Give the user the pointer to write to
					basePtr = ptr->m_pBlockBase;

				}


			}

		}
		


		//Check that there are unused block descriptors and the amount of memory available is greater than what is requested
		if (unusedDescriptorsHead != NULL && getLargestFreeBlock() >= i_size)
		{
			return basePtr;

		}

		//There are no more unused block descriptors
		else
		{
			return NULL;

		}



	}

	bool BlockAllocator::_free(const void * i_ptr)
	{
		
		//The block descriptor to select the outstanding block descriptor to compare
		BlockDescriptor * tempSelected = outstandingDescriptorsHead;

		//The block descriptor to travers the list
		BlockDescriptor * tempPrevious = outstandingDescriptorsHead;

		//The index of the selected block descriptor
		int indexOfDescriptor = 0;

		if (!_isAllocated(i_ptr))
		{
			return false;
		}

		else {
		
			while (tempSelected != NULL) {

				if (tempSelected->m_pBlockBase == i_ptr)
				{

					//Go the previous 
					for (int i = 0; i < indexOfDescriptor - 1; i++)
					{
						tempPrevious = tempPrevious->m_pNext;
					}

					
					if (tempPrevious->m_pNext == NULL) {
						tempSelected->m_pNext = freeDescriptorsHead;
						freeDescriptorsHead = tempSelected;
						outstandingDescriptorsHead = NULL;
						
					}
					else {
						tempPrevious->m_pNext = tempSelected->m_pNext;
						tempSelected->m_pNext = freeDescriptorsHead;
						freeDescriptorsHead = tempSelected;											
					}

					//printf("Free Successful %d\n", k);
					return true;
					break;

				}
				indexOfDescriptor++;
				tempSelected = tempSelected->m_pNext;
			}
			return false;
		}
		
	}



	bool BlockAllocator::_contains(const void * pointer) const
	{
		BlockDescriptor * temp = outstandingDescriptorsHead;

		if (temp == NULL)
		{
			return false;
		}
		else {
			while (temp != NULL)
			{

				if (pointer >= temp->m_pBlockBase && pointer <= reinterpret_cast<unsigned char *>(temp->m_pBlockBase) + temp->m_sizeBlock)
				{
					return true;
					break;
				}

				temp = temp->m_pNext;
			}
		
			return false;
		}
	}

	bool BlockAllocator::_isAllocated(const void * pointer) const
	{
		BlockDescriptor * temp = outstandingDescriptorsHead;
		if (outstandingDescriptorsHead == NULL)
		{
			return false;
		}
		else {
			while (temp != NULL)
			{
				if (pointer == temp->m_pBlockBase)
				{
					return true;
					break;
				}

				temp = temp->m_pNext;
			}
			return false;
		}
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
#ifdef _DEBUG

	void BlockAllocator::PrintBlockDescriptors() const
	{
		//Print the heading of the block allocator
		printf("Block allocator: Total free memory %zu, Lagest Free Block %zu, number of Block descriptors %d\n", getTotalFreeMemory(), getLargestFreeBlock(), totalBlockDescriptors);
		printf("-------------------------------------------------------------------------------------------\n");
		printf("---------------------------Unused Block Descriptors------------------------------\n");


		//Print the list of unused block allocators with their ID and Block Size
		for (BlockDescriptor * ptr = unusedDescriptorsHead; ptr != NULL; ptr = ptr->m_pNext)
		{
			printf("BD: id = %d, Block_size = %zu,Block_Base = %p, Block_Base + Size = %p\n", ptr->m_id, ptr->m_sizeBlock, ptr->m_pBlockBase, reinterpret_cast<unsigned char *>(ptr->m_pBlockBase) + ptr->m_sizeBlock);
		}

		printf("-------------------------------------------------------------------------------------------\n");
		printf("---------------------------Free Block Descriptors------------------------------\n");

		//Print the list of free block allocators with their ID and Block Size
		for (BlockDescriptor * ptr = freeDescriptorsHead; ptr != NULL; ptr = ptr->m_pNext)
		{
			printf("BD: id = %d, Block_size = %zu, Block_Base = %p, Block_Base + Size = %p\n", ptr->m_id, ptr->m_sizeBlock, ptr->m_pBlockBase, reinterpret_cast<unsigned char *>(ptr->m_pBlockBase) + ptr->m_sizeBlock);
		}

		printf("-------------------------------------------------------------------------------------------\n");
		printf("---------------------------Outstanding Block Descriptors------------------------------\n");

		//Print the list of free block allocators with their ID and Block Size
		for (BlockDescriptor * ptr = outstandingDescriptorsHead; ptr != NULL; ptr = ptr->m_pNext)
		{
			printf("BD: id = %d, Block_size = %zu, Block_Base = %p, Block_Base + Size = %p \n", ptr->m_id, ptr->m_sizeBlock, ptr->m_pBlockBase, reinterpret_cast<unsigned char *>(ptr->m_pBlockBase) + ptr->m_sizeBlock);
		}

		printf("-------------------------------------------------------------------------------------------\n");
		printf("-------------------------------------------------------------------------------------------\n");
		printf("-------------------------------------------------------------------------------------------\n");
		printf("-------------------------------------------------------------------------------------------\n");
		printf("-------------------------------------------------------------------------------------------\n");
		printf("-------------------------------------------------------------------------------------------\n");

	}
#endif // _DEBUG

	

	void BlockAllocator::InitializeUnusedDescriptors(const size_t i_sizeMemory, const unsigned int i_numDescriptors)
	{
		totalBlockDescriptors = i_numDescriptors;

		//Split the memory to create a pool of block descriptors
		unsigned char *poolOfBlockDescriptors = (startOfMemory + i_sizeMemory) - (sizeof(BlockDescriptor) * i_numDescriptors);

		for (unsigned int i = 0; i < i_numDescriptors; i++)
		{
			BlockDescriptor* newDescriptor = reinterpret_cast<BlockDescriptor*>(poolOfBlockDescriptors) + i;
			newDescriptor->m_pBlockBase = NULL;
			newDescriptor->m_sizeBlock = 0;

#if _DEBUG
			newDescriptor->m_id = totalBlockDescriptors;
#endif // DEBUG

			totalBlockDescriptors--;
			newDescriptor->m_pNext = unusedDescriptorsHead;
			unusedDescriptorsHead = newDescriptor;

		}
		totalBlockDescriptors = i_numDescriptors;

	}

	void BlockAllocator::SelectionSortBlockDescriptorPointer(BlockDescriptor * const bd_pointer)
	{
		//start pointer
		BlockDescriptor * startPointer = bd_pointer;

		//compare pointer
		BlockDescriptor * comparePointer = startPointer->m_pNext;

		//The minimum size_t
		size_t minimum = 0;
		
		//The indexers to keep track of the location of the smallest sized block descriptor
		int currentIndex = 0;
		int minimumIndex = 0;
		int startIndex = 0;

		//Check that the block Descriptor's next is not null
		while (startPointer->m_pNext != NULL)
		{
			//BlockDescriptor to iterate through the linked list
			BlockDescriptor * iterator = comparePointer;

			//Set the current index to compare to the next after the start
			currentIndex = startIndex + 1;

			while (iterator != NULL)
			{
				//Store the minimum size
				minimum = startPointer->m_sizeBlock;



				//Minimum size and index
				if (minimum > iterator->m_sizeBlock)
				{
					minimumIndex = currentIndex;
					minimum = iterator->m_sizeBlock;
				}
				iterator = iterator->m_pNext;
				currentIndex++;


			}

			iterator = startPointer;

			//Iterate through the linked list to swap the elements
			for (int i = startIndex; i < minimumIndex; i++) {
					
				iterator = iterator->m_pNext;
			}

			//Swap the Block Descriptor Info
			SwapBlockDescriptorInfo(iterator,startPointer);

			//Update the pointers and indexes
			startPointer = startPointer->m_pNext;
			startIndex++;
			comparePointer = comparePointer->m_pNext;
			iterator = comparePointer;
			minimum = startPointer->m_sizeBlock;
			minimumIndex = startIndex;

		}


	}

	void BlockAllocator::SwapBlockDescriptorInfo(BlockDescriptor * lhs_bd_pointer, BlockDescriptor * rhs_bd_pointer)
	{
		//Temporary block descriptor
		void *tempBase;
		size_t tempSize;

		tempBase = rhs_bd_pointer->m_pBlockBase;
		tempSize = rhs_bd_pointer->m_sizeBlock;

		//Swap the rightmost with the leftmost
		rhs_bd_pointer->m_pBlockBase = lhs_bd_pointer->m_pBlockBase;
		rhs_bd_pointer->m_sizeBlock = lhs_bd_pointer->m_sizeBlock;

		//Store the block descriptor info of the temp into the leftmost
		lhs_bd_pointer->m_pBlockBase = tempBase;
		lhs_bd_pointer->m_sizeBlock = tempSize;
	}

	void BlockAllocator::GarabageCollector()
	{

			//Grab the first element in the free list and compare it to all of the others
			BlockDescriptor * temp = freeDescriptorsHead;

			//the block descriptor to compare the current free block descriptor
			BlockDescriptor * iterTemp = freeDescriptorsHead;

			//The previous block descriptor
			BlockDescriptor * previousIterTemp = freeDescriptorsHead;

			//The void pointer to get the calculation of the memory address adjacent to the current free block descriptor
			void * pointerRightSide;

			//The index of the block descriptor that is to be merged
			int indexForMerge = 0;


			while (temp != NULL) {


				pointerRightSide = reinterpret_cast<unsigned char*>(temp->m_pBlockBase) + temp->m_sizeBlock;

				while (iterTemp != NULL){
				

					//printf("Block Base %d, size %zu, address %p, addressNext %p\n", iterTemp->m_id,iterTemp->m_sizeBlock, iterTemp->m_pBlockBase, iterTemp->m_pNext);
					//The block descriptors are adjacent
					if (iterTemp->m_pBlockBase == pointerRightSide) {

						//printf("Block Base Success!! Address %p. nextaddress %p\n", iterTemp->m_pBlockBase, iterTemp->m_pNext);

						//Traverse the free list 
						for (int i = 0; i < indexForMerge - 1;i++)
						{
							//Get the previous free block descriptor from the adjacent one in the list
							previousIterTemp = previousIterTemp->m_pNext;
						}

						if (iterTemp == freeDescriptorsHead)
						{
							freeDescriptorsHead = iterTemp->m_pNext;
						}
						else
						{
							//Assign the next of the previous to the next block descriptor of the selected block descriptor
							previousIterTemp->m_pNext = iterTemp->m_pNext;
						}

						//Increase the size of the new free block descriptor
						temp->m_sizeBlock += iterTemp->m_sizeBlock;						

						//Assign the block descriptor to the unused list of block descriptor
						iterTemp->m_pNext = unusedDescriptorsHead;
						unusedDescriptorsHead = iterTemp;

						//Reset the values of the unused block descriptor
						iterTemp->m_sizeBlock = 0;
						iterTemp->m_pBlockBase = NULL;

						//Reset the iterator block descriptor to the head of the free list
						iterTemp = freeDescriptorsHead;

						//Reset the index
						indexForMerge = 0;

						break;

					}
					indexForMerge++;
					iterTemp = iterTemp->m_pNext;

				}
				indexForMerge = 0;
				iterTemp = freeDescriptorsHead;
				temp = temp->m_pNext;
				
			}

		
	}




}