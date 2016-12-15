#pragma once
#include "FSAManager.h"
#include "FixedBlockAllocator.h"
#include <conio.h>
#include <stdint.h>

void  FSA_UnitTest(Engine::FSAManager * i_fsaManager) {

	//Get a fixed size allocator
	Engine::FixedBlockAllocator * pFsa = i_fsaManager->fixedBlockAllocatorsAvailable[1];

	//Print the amount of available blocks
#ifdef _DEBUG
	pFsa->PrintAvailableBlocks();
#endif
	uint8_t * pointersToTest[20];

	//Test allocating memory
	for (unsigned int i = 0; i < pFsa->GetTotalNumBlocks(); i++)
	{
	pointersToTest[i] = reinterpret_cast<uint8_t  *> (pFsa->_alloc(16));

		if (pointersToTest[i] != NULL)
		{
			for (unsigned int j = 0; j < pFsa->GetBlockSize(); ++j)
			{
			pointersToTest[i][j] = 65 + i;
			}
			#ifdef _DEBUG
			pFsa->PrintAvailableBlocks();
			#endif
		}

			//Ran out of block descriptors
			else {

				//The case where the unused block descriptors are all used
				if (pFsa->GetTotalAvailableBlocks() == 0)
				printf("There are no blocks available\n");
				else
				printf("There is not more free memory available\n");
				_getch();
			break;

		}

	}//end of allocations

#ifdef _DEBUG
	pFsa->PrintAvailableBlocks();
#endif

	bool test = pFsa->GetBitArray()->AreAllSet();
	assert(test == false);

	bool test2 = pFsa->GetBitArray()->IsBitSet(5);
	assert(test2 == false);

	bool test3 = pFsa->GetBitArray()->IsBitSet(20);
	assert(test3 == true);

	//free the blocks from the FSA
	for (unsigned int i = 0; i < pFsa->GetTotalNumBlocks(); i++) {
		for (unsigned int j = 0; j < pFsa->GetBlockSize(); ++j)
		{
			pointersToTest[i][j] = 64;
		}

		pFsa->_free(pointersToTest[i]);

#ifdef _DEBUG
		pFsa->PrintAvailableBlocks();
#endif
	}

	bool test4 = pFsa->GetBitArray()->AreAllSet();
	assert(test4 == true);

	_getch();



}