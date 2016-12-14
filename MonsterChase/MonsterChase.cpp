// MonsterChase.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <assert.h> 
#include <ctime> //For calling a seed of random numbers
#include "Monster.h"
#include "Player.h"
#include "Debug.h"
#include "GameManager.h"
#include "BlockAllocator.h"
#include "NewDelete.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define TRACK_NEW (__FILE__,__FUNCTION__,__LINE__)
#else
#define TRACK_NEW
#endif


//Monster Chase Unit Test
extern void MonsterChase_UnitTest();

//Float Chek unit test
extern void FloatChecker_UnitTest();


//Block allocator unit test
extern bool HeapManager_UnitTest();


//The reverse string in place function
extern char* ReverseString(char * string);

//The bit array unit test
extern void BitArray_UnitTest(void);


extern size_t StringLength(const char * string);


int main()
{
	//MonsterChase_UnitTest();



#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	//For blockAllocator Testing

	//The block allocator
	Engine::BlockAllocator blockAllocator;

	//Creating the block allocator
	blockAllocator.create(1024 * 1024, 100);
	GetBlockAllocator(&blockAllocator);

	//The memory manager that handles FSA
	Engine::FSAManager fsaManager;
	GetFSAManager(&fsaManager);
	fsaManager.CreateFSAs(&blockAllocator);


	//Run the float check unit test
	//FloatChecker_UnitTest();


	//Run the block allocator unit test
	HeapManager_UnitTest();

	_getch();

	//Run the bit array unit test
	//BitArray_UnitTest();



	/*


	

	
	//For Monster Chase
	srand(time_t(0));

	//Create reference to a game manager object
	GameManager* gameManager = new GameManager();

	//Initialize the game
	gameManager->InitializeGame();



	
	//Start of the main game loop
	do
	{
		gameManager->UpdateGameManager();

	}while (gameManager->ReadAdditionalInput() != 'q');


   
	delete gameManager;
	gameManager = nullptr;

	*/

	//{
	//	Monster m1("m1");

	//	// copy constructor
	//	Monster m2 = m1;

	//	//// copy assignment
	//	Monster m3("m3");
	//	m3 = m1;

	//	//// move constructor
	//	Monster m4 = std::move(m2);

	//	//// move assignment
	//	Monster m5("m5");
	//	m5 = std::move(m4);
	//}

	/*

	//Testing for Part 1



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


	return 0;
	*/

	//Monster * monster = new Monster();
	//Monster* monsters = new Monster[4];
	//char* string = new char[10];
	//Monster* monster2 = new TRACK_NEW Monster();

	////_getch();


	//delete monster;
	//delete monster2;
	//delete[] monsters;
	//delete[] string;
	blockAllocator.destroy();
	
	//Reverse string test

	//char word[] = "squirrelled";

	//char * newString = ReverseString(word);

	//DEBUG_LOG_MESSAGE("The new string is: %s", newString);

	//_getch();

	_CrtDumpMemoryLeaks();

	

	return 0;
	
}
