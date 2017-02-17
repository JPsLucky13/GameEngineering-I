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
#include "lua.hpp"
#include "Actor.h"
#include "CreateActor.h"

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
	
	Engine::EngineHandler handler; 
	handler.Init();

	// first we need to initialize GLib
	Engine::Renderer rd;


	//Initialize renderer
	bool bSuccess = rd.Initialize(i_hInstance, i_nCmdShow);

	////String Pool unit test
	//StringPool_UnitTest(&handler.blockAllocator);




	//Check if renderer succeeded
	if (bSuccess)
	{
		Engine::Timer timer;

		//Read input
		Engine::Input::Read();

		

		//DEBUG_LOG_OUTPUT("Position x: %f, Position y: %f", empty->GetPosition().x(), empty->GetPosition().y());

		Engine::SmartPointer<Engine::Actor> player = Engine::CreateActor("Player1.lua");

		


		bool bQuit = false;
		do
		{
			rd.ServiceRenderer(bQuit);

			if (!bQuit)
			{
				rd.StartRenderer();
				rd.StartRenderSprites();
				
				float dt = timer.GetLastFrameTime_ms();

				if (player->getSprite()->sprite)
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
					player->getPhysics()->Update(force,dt);

					GLib::Point2D	Offset = { player->getGObject()->GetPosition().x(), player->getGObject()->GetPosition().y() };
					

					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*player->getSprite()->sprite, Offset, 0.0f);
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
		if (player->getSprite()->sprite)
			GLib::Sprites::Release(player->getSprite()->sprite);
		GLib::Shutdown();
	}
		handler.Shutdown();
#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}

