// MonsterChase.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <assert.h> 
#include <ctime> //For calling a seed of random numbers
#include "Monster.h"
#include "Player.h"
#include "GameManager.h"
#include "BlockAllocator.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//Monster Chase Unit Test
extern void MonsterChase_UnitTest();

//Block allocator unit test
extern bool HeapManager_UnitTest();

int main()
{
	//MonsterChase_UnitTest();



#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG


	//Run the block allocator unit test
	//HeapManager_UnitTest();

	//_getch();




	//For Monster Chase
	srand(time_t(0));

	//Create reference to a game manager object
	GameManager gameManager;

	//Initialize the game
	gameManager.InitializeGame();



	
	//Start of the main game loop
	do
	{
		gameManager.UpdateGameManager();

	}while (gameManager.ReadAdditionalInput() != 'q');


    return 0;






	//For blockAllocator Testing

	//The block allocator
	//Engine::BlockAllocator blockAllocator;

	//Creating the block allocator
	//blockAllocator.create(1024, 10);
	
	//Testing for Part 1

	/*

	//Test allocating memory
	for (int i = 0; i < 10; i++)
	{
		//blockAllocator._alloc(pow(16.0, i + 1));
		if (blockAllocator._alloc(32+i) != NULL)
		{
			blockAllocator.PrintBlockDescriptors();
			//Halt the operation
			_getch();
		}

		//Ran out of block descriptors
		else {



			

			//The case where the unused block descriptors are all used
			if (blockAllocator.unusedDescriptorsHeadGetter() == NULL)
				printf("There are no more unused block descriptors available\n");
			else
				printf("There is not more free memory available\n");
			_getch();
			break;
			
		}

	}

	*/
	
	//Testing for part 2
	/*
	char * pointersToTest[5];

	//Test allocating memory
	for (unsigned int i = 0; i < 5; i++)
	{
		size_t requestSize = 32 + i;
		pointersToTest[i] =reinterpret_cast<char *> (blockAllocator._alloc(requestSize));

		//blockAllocator._alloc(pow(16.0, i + 1));
		if (pointersToTest[i] != NULL)
		{
			for (unsigned int j = 0; j < requestSize; ++j)
			{
				pointersToTest[i][j] = i + 65;
			}
#ifdef _DEBUG
			blockAllocator.PrintBlockDescriptors();
#endif
			//Halt the operation
			_getch();
		}

		//Ran out of block descriptors
		else {

			//The case where the unused block descriptors are all used
			if (blockAllocator.unusedDescriptorsHeadGetter() == NULL)
				printf("There are no more unused block descriptors available\n");
			else
				printf("There is not more free memory available\n");
			_getch();
			break;

		}

	}

	for (unsigned int i = 0; i < 5; i++) {
		for (unsigned int j = 0; j < (32 + i); ++j)
		{
			pointersToTest[i][j] = 64;
		}
	
		blockAllocator._free(pointersToTest[i]);

		//blockAllocator.k++;

#ifdef _DEBUG
		blockAllocator.PrintBlockDescriptors();
#endif
		
		//Halt the operation
		_getch();
	}

	
	blockAllocator._alloc(36);
	
#ifdef _DEBUG
	blockAllocator.PrintBlockDescriptors();
#endif

	//Halt the operation
	_getch();

	blockAllocator.GarabageCollector();

#ifdef _DEBUG
	blockAllocator.PrintBlockDescriptors();
#endif
	//Halt the operation
	_getch();
	
	blockAllocator.destroy();

	_CrtDumpMemoryLeaks();

	*/
	return 0;

}
