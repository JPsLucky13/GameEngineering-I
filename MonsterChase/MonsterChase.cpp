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
#include "PhysicsInfo.h"
#include "Sprite.h"
#include "GameObject.h"
#include <Windows.h>
#include "Timer.h"
#include "SmartPointer.h"
#include "WeakPointer.h"


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

	//SmartPointer Unit Test




	//Check if renderer succeeded
	if (bSuccess)
	{
		Engine::Timer timer;

		//Read input
		Engine::Input::Read();

		//The game play
		Engine::SmartPointer<Engine::GameObject> gameObjectPlayer(new Engine::GameObject());
		Engine::SmartPointer<Engine::GameObject> dummy(std::move(gameObjectPlayer));
		Engine::PhysicsInfo * physicsInPlayer = new Engine::PhysicsInfo(dummy,1.0f,0.05f);

		//Engine::SmartPointer<Engine::GameObject> gameObjectMonster(new Engine::GameObject());
		//Engine::PhysicsInfo * physicsInMonster = new Engine::PhysicsInfo(gameObjectMonster, 1.0f, 1.0f);


		// Create a couple of sprites using our own helper routine CreateSprite
		Engine::WeakPointer<Engine::GameObject> playerObject(dummy);
		Engine::SmartPointer<Engine::GameObject> empty = playerObject.Acquire();
		assert(dummy == empty);
		Engine::Sprite * playerSprite = new Engine::Sprite(playerObject, "data\\Zero.dds");
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

				if (playerSprite->sprite)
				{
					Engine::Vector2D force(0.0f, 0.0f);
					const float forceMagnitude = 5.0f;

					//Move the player
					if (Engine::Input::keyHandler.A.m_isDown)
					{
						force = Engine::Vector2D(-forceMagnitude,0.0f);
					}

					if (Engine::Input::keyHandler.S.m_isDown)
					{
						force = Engine::Vector2D(0.0f, -forceMagnitude);
					}

					if (Engine::Input::keyHandler.W.m_isDown)
					{
						force = Engine::Vector2D(0.0f, forceMagnitude);
					}

					if (Engine::Input::keyHandler.D.m_isDown)
					{
						force = Engine::Vector2D(forceMagnitude, 0.0f);
					}

					if (Engine::Input::keyHandler.Q.m_isDown)
					{
						bQuit = true;
					}


					//Update the physics
					physicsInPlayer->Update(force,dt);

					GLib::Point2D	Offset = { dummy->GetPosition().x() , dummy->GetPosition().y()};
					
					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*playerSprite->sprite, Offset, 0.0f);
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
		if (playerSprite->sprite)
			GLib::Sprites::Release(playerSprite->sprite);
		GLib::Shutdown();

		//Delete the pointers
		delete physicsInPlayer;
		delete playerSprite;
	}
		handler.Shutdown();
#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}

