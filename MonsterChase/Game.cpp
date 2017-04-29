#pragma once
#include "Game.h"
#include "ProfilerUtils.h"




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


				//Player Movement

				//Force to move the player
				Engine::Vector2D force(0.0f, 0.0f);
				const float forceMagnitude = 10.0f;

				//Force for the monsters
				Engine::Vector2D monster_force(0.0f, 0.0f);

				//Move the player
				if (Engine::Input::keyHandler.A.m_isDown)
				{
					force = Engine::Vector2D(-forceMagnitude, 0.0f);
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

				actorMu.Acquire();
				//For loop to update the actors
				for (size_t i = 0; i < actorsInScene.size(); i++)
				{


					//Update the player movement
 					if (strcmp(actorsInScene[i]->getName(), "Zero") == 0)
					{
						actorsInScene[i]->getPhysics().Acquire()->Update(force, dt);
					}
					else
					{
						actorsInScene[i]->getPhysics().Acquire()->Update(monster_force, dt);
					}


					float rotation = actorsInScene[i]->getGObject()->GetRotation().z();
					GLib::Point2D	Offset = { actorsInScene[i]->getGObject()->GetPosition().x(), actorsInScene[i]->getGObject()->GetPosition().y() };

					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*actorsInScene[i]->getSprite().Acquire()->sprite, Offset, rotation);


					//Handle collisions without velocity and with rotations
					if (actorsInScene.size() > 1)
					{
						PROFILE_UNSCOPED("Engine::Collision::CheckCollisions");
						Engine::Collision::CheckCollisions(actorsInScene, dt);
						PROFILE_SCOPE_END();
					}

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

void Game::UpdateNewActors()
{
	actorMu.Acquire();

	if (actorsToAdd.size() > 0)
	{
		Engine::SmartPointer<Engine::Actor> temp = actorsToAdd.back();
		actorsToAdd.pop_back();
		actorsInScene.push_back(temp);
	}

	actorMu.Release();

}
