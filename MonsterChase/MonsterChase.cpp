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
#include "Game.h"
#include "PhysicsInfo.h"
#include "Sprite.h"
#include "GameObject.h"
#include <Windows.h>
#include "EngineHandler.h"
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

//String pool unit test
//extern void StringPool_UnitTest(Engine::BlockAllocator * i_pBlockAllocator);

//FSA Unite test
//extern void FSA_UnitTest(Engine::FSAManager * i_fsaManager);


//The reverse string in place function
extern char* ReverseString(char * string);

//The bit array unit test
extern void BitArray_UnitTest(void);


extern size_t StringLength(const char * string);






int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG
	
	//Initialize the engine for memory allocation
	Engine::EngineHandler m_handler;
	m_handler.Init();

	bool startGame = true;

	if(startGame)
	{ 
		//initialize the game
		Game game;
		game.InitializeGame(i_hPrevInstance, i_nCmdShow);
		if (!game.StartGameLoop())
		{
			Engine::ThreadedFileProcessor::Shutdown();	
			startGame = false;
		}
	}
	//Shutdown the engine for memory allocation
	m_handler.Shutdown();
	
#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}

