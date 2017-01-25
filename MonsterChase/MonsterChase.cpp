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
#include "EngineHandler.h"
#include "Input.h"
#include "Renderer.h"

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
	
	Engine::EngineHandler handler; 
	handler.Init();

	// first we need to initialize GLib
	Engine::Renderer rd;

	//Initialize renderer
	bool bSuccess = rd.Initialize(i_hInstance, i_nCmdShow);

	//Check if renderer succeeded
	if (bSuccess)
	{
		//Read input
		Engine::Read();

		// Create a couple of sprites using our own helper routine CreateSprite
		GLib::Sprites::Sprite * pGoodGuy = rd.CreateSprite("data\\Zero.dds");
		GLib::Sprites::Sprite * pBadGuy = rd.CreateSprite("data\\Vile.dds");

		bool bQuit = false;
		do
		{
			rd.ServiceRenderer(bQuit);

			if (!bQuit)
			{
				rd.StartRenderer();
				rd.StartRenderSprites();
				
				
				if (pGoodGuy)
				{
					static float			moveDist = .01f;
					static float			moveDir = moveDist;
					static GLib::Point2D	Offset = { -180.0f, -100.0f };
					if (Offset.x < -220.0f)
						moveDir = moveDist;
					else if (Offset.x > -140.0f)
						moveDir = -moveDist;
					Offset.x += moveDir;
					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*pGoodGuy, Offset, 0.0f);
				}
				if (pBadGuy)
				{
					static float			moveDist = .02f;
					static float			moveDir = -moveDist;
					static GLib::Point2D	Offset = { 180.0f, -100.0f };
					if (Offset.x > 200.0f)
						moveDir = -moveDist;
					else if (Offset.x < 160.0f)
						moveDir = moveDist;
					Offset.x += moveDir;
					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*pBadGuy, Offset, 0.0f);
				}
				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// Tell GLib we're done rendering
				GLib::EndRendering();
			}
		} while (bQuit == false);
		if (pGoodGuy)
			GLib::Sprites::Release(pGoodGuy);
		if (pBadGuy)
			GLib::Sprites::Release(pBadGuy);
		GLib::Shutdown();

		handler.Shutdown();
	}
#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}

