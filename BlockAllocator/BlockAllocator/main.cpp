#include "BlockAllocator.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>





int main()
{
	//printf("Size of descriptor:%zd\n", sizeof(BlockAllocator::BlockDescriptor));

	//_getch();

	//The block allocator
	BlockAllocator blockAllocator;

	//Creating the block allocator
	blockAllocator.create(1024,10);

	//printf("Size: %d", sizeof(BlockAllocator::BlockDescriptor));
	


	//Test allocating memory
	for (int i = 0; i < 10; i++)
	{
		//blockAllocator._alloc(pow(16.0, i + 1));
		if (blockAllocator._alloc(128) != NULL)
		{
			blockAllocator.PrintBlockDescriptors();
			//Halt the operation
			_getch();

		}

		//Ran out of block descriptors
		else {


			//The case where the unused block descriptors are all used
			if(blockAllocator.unusedDescriptorsHeadGetter() == NULL)
			printf("There are no more unused block descriptors available\n");
			else
			printf("There is not more free memory available\n");
			_getch();
			break;
		}
	
	}



	

	/*
	BlockAllocator::BlockDescriptor * head = (BlockAllocator::BlockDescriptor *)_aligned_malloc(sizeof(BlockAllocator::BlockDescriptor)*2,4);

	BlockAllocator::BlockDescriptor * head2 = head + sizeof(BlockAllocator::BlockDescriptor);

	printf("Head %p, Head2 %p, Substraction %d/n",head, head2, head2 - head);

	_getch();
	*/
	return 0;
}

