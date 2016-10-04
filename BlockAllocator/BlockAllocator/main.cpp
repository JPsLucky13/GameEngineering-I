#include "BlockAllocator.h"

#include <stdio.h>
#include <conio.h>

int main()
{
	printf("Size of descriptor:%zd\n", sizeof(BlockAllocator::BlockDescriptor));

	_getch();

	return 0;
}