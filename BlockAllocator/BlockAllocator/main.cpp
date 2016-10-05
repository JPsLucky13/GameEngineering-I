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
	blockAllocator.create(4096,10);

	//printf("Size: %d", sizeof(BlockAllocator::BlockDescriptor));
	


	//Test allocating memory
	for (int i = 0; i < 10; i++)
	{
		//blockAllocator._alloc(pow(16.0, i + 1));
		blockAllocator._alloc(16);
		

		blockAllocator.PrintBlockDescriptors();
		//Halt the operation
		_getch();
		
	}



	

	/*
	BlockAllocator::BlockDescriptor * head = (BlockAllocator::BlockDescriptor *)_aligned_malloc(sizeof(BlockAllocator::BlockDescriptor)*2,4);

	BlockAllocator::BlockDescriptor * head2 = head + sizeof(BlockAllocator::BlockDescriptor);

	printf("Head %p, Head2 %p, Substraction %d/n",head, head2, head2 - head);

	_getch();
	*/
	return 0;
}

