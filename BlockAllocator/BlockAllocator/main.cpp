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
<<<<<<< HEAD
	blockAllocator.create(1024, 10);
=======
	blockAllocator.create(1024,10);
>>>>>>> 836e5fea4cb4c7d6d489ce4bbc3a15d2b3bac17a

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
<<<<<<< HEAD
			if (blockAllocator.unusedDescriptorsHeadGetter() == NULL)
				printf("There are no more unused block descriptors available\n");
			else
				printf("There is not more free memory available\n");
			_getch();
			break;
		}

=======
			if(blockAllocator.unusedDescriptorsHeadGetter() == NULL)
			printf("There are no more unused block descriptors available\n");
			else
			printf("There is not more free memory available\n");
			_getch();
			break;
		}
	
>>>>>>> 836e5fea4cb4c7d6d489ce4bbc3a15d2b3bac17a
	}





	/*
	BlockAllocator::BlockDescriptor * head = (BlockAllocator::BlockDescriptor *)_aligned_malloc(sizeof(BlockAllocator::BlockDescriptor)*2,4);

	BlockAllocator::BlockDescriptor * head2 = head + sizeof(BlockAllocator::BlockDescriptor);

	printf("Head %p, Head2 %p, Substraction %d/n",head, head2, head2 - head);

	_getch();
	*/
	return 0;
}