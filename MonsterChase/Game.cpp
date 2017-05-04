#pragma once
#include "Game.h"
#include "ProfilerUtils.h"
#include "Debug.h"



//Singletons
Engine::Physics * Game::physics = NULL;
Engine::Renderer * Game::renderer = NULL;
Engine::MessageSystem * Game::messageSystem = NULL;
Engine::Timer * Game::timer = NULL;

Game::Game():
	actorMu(false, "ActorsMutex")
{
	
}

Game::~Game()
{

}


void Game::InitializeGame(HINSTANCE i_hInstance, int i_nCmdShow)
{

	//Initialize physics
	physics = Engine::Physics::Create();

	//Initialize renderer
	renderer = Engine::Renderer::Create();

	//Initialize the message system
	messageSystem = Engine::MessageSystem::Create();

	//Initialize the timer
	timer = Engine::Timer::Create();

	//Initialize renderer
	m_renderSuccess = renderer->Initialize(i_hInstance, i_nCmdShow);

	//Set up handler for detecting actor creation
	Engine::MessageSystem::GetInstance()->RegisterMessageHandler("ActorCreated", std::bind(&Game::UpdateNewActors, this));
}

bool Game::StartGameLoop()
{
	//Check if renderer succeeded
	if (m_renderSuccess)
	{

		
		//Read input
		Engine::Input::Read();

		Engine::ThreadedFileProcessor &Processor = Engine::ThreadedFileProcessor::GetInstance();

		Processor.AddToLoadQueue(*new Engine::ShowTask("..//data/Player1.lua", "Player1", actorsToAdd, actorMu));
		Processor.AddToLoadQueue(*new Engine::ShowTask("..//data/Monster1.lua", "Monster1", actorsToAdd, actorMu));

		bool bQuit = false;
		do
		{
			renderer->ServiceRenderer(bQuit);

			if (!bQuit)
			{
				renderer->StartRenderer();
				renderer->StartRenderSprites();

				float dt = timer->GetLastFrameTime_ms();

				//Load the level background
				if(!donePlacingPlatforms)
				LoadLevelPlatforms();


				//Player Movement

				//Force to move the player
				Engine::Vector2D force(0.0f, 0.0f);
				const float forceMagnitude = 200.0f;

				//Force for the monsters
				Engine::Vector2D monster_force(-forceMagnitude, 0.0f);

				//Move the player
				if (Engine::Input::keyHandler.A.m_isDown)
				{
					force = Engine::Vector2D(-forceMagnitude, 0.0f);
				}

				if (Engine::Input::keyHandler.D.m_isDown)
				{
					force = Engine::Vector2D(forceMagnitude, 0.0f);
				}

				//Quit the game by pressing 'Q'
				if (Engine::Input::keyHandler.Q.m_isDown)
				{
					bQuit = true;
				}

				actorMu.Acquire();
				//For loop to update the actors
				for (size_t i = 0; i < actorsInScene.size(); i++)
				{
					//Handle collisions without velocity and with rotations
					if (actorsInScene.size() > 1)
					{
						PROFILE_UNSCOPED("Engine::Collision::CheckCollisions");
						Engine::Collision::CheckCollisions(actorsInScene, dt);
						PROFILE_SCOPE_END();
					}

					//Update the player movement
 					if (actorsInScene[i]->getType() == "Player")
					{
						actorsInScene[i]->getPhysics().Acquire()->Update(force, dt);
						DEBUG_LOG_OUTPUT("Velocity: x: %f, y: %f", actorsInScene[i]->getGObject()->GetVelocity().x(), actorsInScene[i]->getGObject()->GetVelocity().y());
					}
					else if (actorsInScene[i]->getType() == "Monster")
					{
						actorsInScene[i]->getPhysics().Acquire()->Update(monster_force, dt);
					}


					float rotation = actorsInScene[i]->getGObject()->GetRotation().z();
					GLib::Point2D	Offset = { actorsInScene[i]->getGObject()->GetPosition().x(), actorsInScene[i]->getGObject()->GetPosition().y() };

					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*actorsInScene[i]->getSprite().Acquire()->sprite, Offset, rotation);
				}
				actorMu.Release();
				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// Tell GLib we're done rendering
				GLib::EndRendering();
			}
		} while (bQuit == false);

		for (size_t i = 0; i < actorsInScene.size(); i++)
		{

			GLib::Sprites::Release(actorsInScene[i]->getSprite().Acquire()->sprite);
		}
		GLib::Shutdown();
	}

	return false;


}

void Game::LoadLevelPlatforms()
{

	if(numberOfPlatforms < maxNumberOfPlatforms){

	//Get the processor instance
	Engine::ThreadedFileProcessor &Processor = Engine::ThreadedFileProcessor::GetInstance();

	Processor.AddToLoadQueue(*new Engine::ShowTask("..//data/Block.lua", "Block", actorsToAdd, actorMu));
	}

	numberOfPlatforms++;


	if (platforms.size() == maxNumberOfPlatforms && !donePlacingPlatforms)
	{
		//The first platform
		platforms[0]->getGObject()->SetRotation(Engine::Vector3(0.0f,0.0f, 1.5708f));
		platforms[0]->getGObject()->SetPosition(Engine::Vector2D(-340.0f,200.0f));

		//The second platform
		platforms[1]->getGObject()->SetRotation(Engine::Vector3(0.0f, 0.0f, 1.5708f));
		platforms[1]->getGObject()->SetPosition(Engine::Vector2D(-340.0f, 20.0f));

		//The third platform
		platforms[2]->getGObject()->SetRotation(Engine::Vector3(0.0f, 0.0f, 1.5708f));
		platforms[2]->getGObject()->SetPosition(Engine::Vector2D(-340.0f, -160.0f));

		//The fourth platform
		platforms[3]->getGObject()->SetRotation(Engine::Vector3(0.0f, 0.0f, 0.0f));
		platforms[3]->getGObject()->SetPosition(Engine::Vector2D(-310.0f, -300.0f));

		//The fifth platform
		platforms[4]->getGObject()->SetRotation(Engine::Vector3(0.0f, 0.0f, 0.0f));
		platforms[4]->getGObject()->SetPosition(Engine::Vector2D(-140.0f, -300.0f));

		//The sixth platform
		platforms[5]->getGObject()->SetRotation(Engine::Vector3(0.0f, 0.0f, 0.0f));
		platforms[5]->getGObject()->SetPosition(Engine::Vector2D(30.0f, -300.0f));

		////The seventh platform
		platforms[6]->getGObject()->SetRotation(Engine::Vector3(0.0f, 0.0f, 0.0f));
		platforms[6]->getGObject()->SetPosition(Engine::Vector2D(210.0f, -300.0f));

		//The eigth platform
		platforms[7]->getGObject()->SetRotation(Engine::Vector3(0.0f, 0.0f, 0.0f));
		platforms[7]->getGObject()->SetPosition(Engine::Vector2D(390.0f, -300.0f));

		//The ninth platform
		platforms[8]->getGObject()->SetRotation(Engine::Vector3(0.0f, 0.0f, 1.5708f));
		platforms[8]->getGObject()->SetPosition(Engine::Vector2D(400.0f, -160.0f));

		//The tenth platform
		platforms[9]->getGObject()->SetRotation(Engine::Vector3(0.0f, 0.0f, 1.5708f));
		platforms[9]->getGObject()->SetPosition(Engine::Vector2D(400.0f, 20.0f));

		//The eleventh platform
		platforms[10]->getGObject()->SetRotation(Engine::Vector3(0.0f, 0.0f, 1.5708f));
		platforms[10]->getGObject()->SetPosition(Engine::Vector2D(400.0f, 200.0f));

		
		donePlacingPlatforms = true;
	}
}

void Game::UpdateNewActors()
{
	actorMu.Acquire();

	if (actorsToAdd.size() > 0)
	{
		Engine::SmartPointer<Engine::Actor> temp = actorsToAdd.back();
		actorsToAdd.pop_back();
		actorsInScene.push_back(temp);
	
		//Add the platfrom to the vector of platforms
		if (temp->getType() == "Level")
		{
			platforms.push_back(temp);
		}
	
	}

	actorMu.Release();

}
