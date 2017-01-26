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
#include "KeyboardHandler.h"
#include "PhysicsInfo.h"
#include "Sprite.h"
#include "GameObject.h"
#include <Windows.h>
#include "Timer.h"

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

	//Create a keyboad handler
	Engine::KeyboardHandler * keyboard;


	//Initialize renderer
	bool bSuccess = rd.Initialize(i_hInstance, i_nCmdShow);




	//Check if renderer succeeded
	if (bSuccess)
	{
		Engine::Timer timer;
	


		//Read input
		Engine::Read();

		//The game play
		Engine::GameObject * gameObjectPlayer;
		Engine::PhysicsInfo * physicsInPlayer = new Engine::PhysicsInfo(gameObjectPlayer,1.0f,1.0f);

		Engine::GameObject * gameObjectMonster;
		Engine::PhysicsInfo * physicsInMonster = new Engine::PhysicsInfo(gameObjectMonster, 1.0f, 1.0f);


		// Create a couple of sprites using our own helper routine CreateSprite
		Engine::Sprite * playerSprite = new Engine::Sprite(gameObjectPlayer, "data\\Zero.dds");
		//Engine::Sprite *  monsterSprite = new Engine::Sprite(gameObjectMonster, "data\\Vile.dds");



		bool bQuit = false;
		do
		{
			rd.ServiceRenderer(bQuit);

			if (!bQuit)
			{
				rd.StartRenderer();
				rd.StartRenderSprites();
				
				float dt = timer.GetLastFrameTime_ms();



				if (playerSprite.sprite)
				{
					Engine::Vector2D force;


					//Move the player
					if (Engine::keyHandler->A.m_isDown)
					{
						force = Engine::Vector2D(-1.0f,0.0f);
					}

					if (Engine::keyHandler->S.m_isDown)
					{
						force = Engine::Vector2D(0.0f, -1.0f);
					}

					if (Engine::keyHandler->W.m_isDown)
					{
						force = Engine::Vector2D(0.0f, 1.0f);
					}

					if (Engine::keyHandler->D.m_isDown)
					{
						force = Engine::Vector2D(1.0f, 0.0f);
					}

					static GLib::Point2D	Offset = { gameObjectPlayer->GetPosition().x , gameObjectPlayer->GetPosition().y};

					//Update the physics
					physicsInPlayer.Update(force,dt);

					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*playerSprite.sprite, Offset, 0.0f);
				}
				//if (monster)
				//{
					// Tell GLib to render this sprite at our calculated location
				//	GLib::Sprites::RenderSprite(*monster, Offset, 0.0f);
				//}
				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// Tell GLib we're done rendering
				GLib::EndRendering();
			}
		} while (bQuit == false);
		if (playerSprite.sprite)
			GLib::Sprites::Release(playerSprite.sprite);
		GLib::Shutdown();

		handler.Shutdown();
	}
#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}

