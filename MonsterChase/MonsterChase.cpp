// MonsterChase.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <assert.h> 
#include <vector>
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
#include "Physics.h"
#include "ThreadedFileProcessor.h"
#include "ShowTask.h"
#include "Matrix4x4.h"
#include "Vector4.h"

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

void CheckForNewActors(std::vector<Engine::SmartPointer<Engine::Actor>>& i_actorsToAdd, std::vector<Engine::SmartPointer<Engine::Actor>>& i_actorsInScene, Engine::Mutex& i_actor)
{
	i_actor.Acquire();

	if (i_actorsToAdd.size() > 0)
	{
		Engine::SmartPointer<Engine::Actor> temp = i_actorsToAdd.back();
		i_actorsToAdd.pop_back();
		i_actorsInScene.push_back(temp);
	}

	i_actor.Release();

}




int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG
	
	//Initialize the engine for memory allocation
	Engine::EngineHandler handler; 
	handler.Init();

	//Initialize physics
	static Engine::Physics * physics;
	physics = Engine::Physics::Create();

	//Initialize renderer
	static Engine::Renderer * renderer;
	renderer = Engine::Renderer::Create();

	//Initialize renderer
	bool bSuccess = renderer->Initialize(i_hInstance, i_nCmdShow);

	////String Pool unit test
	//StringPool_UnitTest(&handler.blockAllocator);


	//Check if renderer succeeded
	if (bSuccess)
	{
		Engine::Timer timer;

		//Read input
		Engine::Input::Read();

		

		//DEBUG_LOG_OUTPUT("Position x: %f, Position y: %f", empty->GetPosition().x(), empty->GetPosition().y());

		//Vectors of actors
		std::vector<Engine::SmartPointer<Engine::Actor>> actorsToAdd;
		std::vector<Engine::SmartPointer<Engine::Actor>> actorsInScene;

		Engine::ThreadedFileProcessor &Processor = Engine::ThreadedFileProcessor::GetInstance();

		Engine::Mutex actorMu(false, "ActorsMutex");
		Processor.AddToLoadQueue(*new Engine::ShowTask("..//data/Player1.lua","Player1", actorsToAdd, actorMu));


		//Test case for matrices and Vector4
		Engine::Matrix4x4 A(5,6,7,8,
							 0,1,0,1,
							 2,3,1,2,
							 0,0,0,1);

		Engine::Matrix4x4 B(7,9,4,5,
							2,3,3,1,
							1,1,0,0,
							2,6,7,5);


		Engine::Matrix4x4 C = A*B;


		DEBUG_LOG_OUTPUT(" Matrix C \n  m_11: %f, m_12: %f, m_13: %f, m_14: %f \n  m_21: %f, m_22: %f, m_23: %f, m_24: %f \n m_31: %f, m_32: %f, m_33: %f, m_34: %f \n m_41: %f, m_42: %f, m_43: %f, m_44: %f \n", C._11(), C._12(), C._13(), C._14(), C._21(), C._22(), C._23(), C._24(), C._31(), C._32(), C._33(), C._34(), C._41(), C._42(), C._43(), C._44());

		//Transpose of A copy
		C = A.GetTranspose();
		DEBUG_LOG_OUTPUT(" Transpose \n m_11: %f, m_12: %f, m_13: %f, m_14: %f \n  m_21: %f, m_22: %f, m_23: %f, m_24: %f \n m_31: %f, m_32: %f, m_33: %f, m_34: %f \n m_41: %f, m_42: %f, m_43: %f, m_44: %f \n", C._11(), C._12(), C._13(), C._14(), C._21(), C._22(), C._23(), C._24(), C._31(), C._32(), C._33(), C._34(), C._41(), C._42(), C._43(), C._44());

		//Transpose of A
		//A.Transpose();
		//DEBUG_LOG_OUTPUT(" Matrix A T \n m_11: %f, m_12: %f, m_13: %f, m_14: %f \n  m_21: %f, m_22: %f, m_23: %f, m_24: %f \n m_31: %f, m_32: %f, m_33: %f, m_34: %f \n m_41: %f, m_42: %f, m_43: %f, m_44: %f \n", A._11(), A._12(), A._13(), A._14(), A._21(), A._22(), A._23(), A._24(), A._31(), A._32(), A._33(), A._34(), A._41(), A._42(), A._43(), A._44());

		

		//Inverse of A
		C = A.GetInverse();

		DEBUG_LOG_OUTPUT(" Inverse \n m_11: %f, m_12: %f, m_13: %f, m_14: %f \n  m_21: %f, m_22: %f, m_23: %f, m_24: %f \n m_31: %f, m_32: %f, m_33: %f, m_34: %f \n m_41: %f, m_42: %f, m_43: %f, m_44: %f \n", C._11(), C._12(), C._13(), C._14(), C._21(), C._22(), C._23(), C._24(), C._31(), C._32(), C._33(), C._34(), C._41(), C._42(), C._43(), C._44());



		//Invert A
		A.Invert();
		DEBUG_LOG_OUTPUT(" A -1 \n m_11: %f, m_12: %f, m_13: %f, m_14: %f \n  m_21: %f, m_22: %f, m_23: %f, m_24: %f \n m_31: %f, m_32: %f, m_33: %f, m_34: %f \n m_41: %f, m_42: %f, m_43: %f, m_44: %f \n", A._11(), A._12(), A._13(), A._14(), A._21(), A._22(), A._23(), A._24(), A._31(), A._32(), A._33(), A._34(), A._41(), A._42(), A._43(), A._44());

		//Rotation Matrix Z
		Engine::Matrix4x4 Rotz = Engine::Matrix4x4::CreateZRotation(3.14f);
		DEBUG_LOG_OUTPUT(" Rotation Z \n m_11: %f, m_12: %f, m_13: %f, m_14: %f \n  m_21: %f, m_22: %f, m_23: %f, m_24: %f \n m_31: %f, m_32: %f, m_33: %f, m_34: %f \n m_41: %f, m_42: %f, m_43: %f, m_44: %f \n", Rotz._11(), Rotz._12(), Rotz._13(), Rotz._14(), Rotz._21(), Rotz._22(), Rotz._23(), Rotz._24(), Rotz._31(), Rotz._32(), Rotz._33(), Rotz._34(), Rotz._41(), Rotz._42(), Rotz._43(), Rotz._44());
		Engine::Matrix4x4 trans = Engine::Matrix4x4::CreateTranslation(Engine:: Vector4(2.0f,3.0f,1.0f,5.0f));
		Rotz = Rotz * trans;
		DEBUG_LOG_OUTPUT(" Rotation Z X Translation \n m_11: %f, m_12: %f, m_13: %f, m_14: %f \n  m_21: %f, m_22: %f, m_23: %f, m_24: %f \n m_31: %f, m_32: %f, m_33: %f, m_34: %f \n m_41: %f, m_42: %f, m_43: %f, m_44: %f \n", Rotz._11(), Rotz._12(), Rotz._13(), Rotz._14(), Rotz._21(), Rotz._22(), Rotz._23(), Rotz._24(), Rotz._31(), Rotz._32(), Rotz._33(), Rotz._34(), Rotz._41(), Rotz._42(), Rotz._43(), Rotz._44());

		Engine::Vector4 result = Rotz.MultiplyRight(Engine::Vector4(2.0f, 0.0f, 1.0f, 0.0f));

		DEBUG_LOG_OUTPUT(" Vector4 result \n m_x: %f, m_y: %f, m_z: %f, m_w: %f \n", result.x(), result.y() , result.z(), result.w());

		bool bQuit = false;
		do
		{
			renderer->ServiceRenderer(bQuit);

			if (!bQuit)
			{
				renderer->StartRenderer();
				renderer->StartRenderSprites();
				
				float dt = timer.GetLastFrameTime_ms();

				//if (player->getSprite().Acquire()->sprite)
				//{
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


					//For loop to update the actors
					for(size_t i = 0; i < actorsInScene.size(); i++)
					{
						actorsInScene[i]->getPhysics().Acquire()->Update(force, dt);
						GLib::Point2D	Offset = { actorsInScene[i]->getGObject()->GetPosition().x(), actorsInScene[i]->getGObject()->GetPosition().y() };
					
						// Tell GLib to render this sprite at our calculated location
						GLib::Sprites::RenderSprite(*actorsInScene[i]->getSprite().Acquire()->sprite, Offset, 0.0f);
					}
					
					CheckForNewActors(actorsToAdd, actorsInScene, actorMu);


					

					
				//}
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
		//if (player->getSprite().Acquire()->sprite)
		for (size_t i = 0; i < actorsInScene.size(); i++)
		{
		
			GLib::Sprites::Release(actorsInScene[i]->getSprite().Acquire()->sprite);
		}
		GLib::Shutdown();
	}
	Engine::ThreadedFileProcessor::Shutdown();
	handler.Shutdown();
#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}

