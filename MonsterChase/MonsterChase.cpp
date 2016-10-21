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


int main()
{
	//For Monster Chase
	/*
	srand(time_t(0));

	//Create reference to a game manager object
	GameManager gameManager;

	//Initialize the game
	gameManager.InitializeGame();
	
	//Start of the main game loop
	do
	{
		gameManager.updateGameManager();

	}while (gameManager.PlayerOptions() != 'q');


    return 0;

	*/

	//For blockAllocator Testing

	//The block allocator
	Engine::BlockAllocator blockAllocator;

	//Creating the block allocator
	blockAllocator.create(1024, 10);

	//printf("Size: %d", sizeof(BlockAllocator::BlockDescriptor));
	
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

	char * pointersToTest[5];

	//Test allocating memory
	for (int i = 0; i < 5; i++)
	{

		pointersToTest[i] =(char*) blockAllocator._alloc(32 + i);

		//blockAllocator._alloc(pow(16.0, i + 1));
		if (pointersToTest[i] != NULL)
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

	for (int i = 0; i < 5; i++) {
	
		blockAllocator._free(pointersToTest[i]);

		blockAllocator.k++;

		blockAllocator.PrintBlockDescriptors();
		//Halt the operation
		_getch();

	}




	return 0;

}
