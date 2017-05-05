#pragma once
#include "Game.h"
#include "ProfilerUtils.h"
#include "Debug.h"
#include <stdlib.h>     
#include <time.h> 


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

	//Set up handler for detecting actor collision
	Engine::MessageSystem::GetInstance()->RegisterMessageHandlerCollision("ResolveCollision", std::bind(&Game::OnCollision, this, std::placeholders::_1, std::placeholders:: _2));

	//Fill the array of enemy spawn positions
	enemySpawnPositions[0] = Engine::Vector2D(200.0f, 200.0f);
	enemySpawnPositions[1] = Engine::Vector2D(200.0f, -100.0f);
	enemySpawnPositions[2] = Engine::Vector2D(200.0f, -200.0f);

	srand(NULL);
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

				//Load the bullets
				if (!doneLoadingBullets)
				LoadBullets();

				//Load the enemies
				if (!doneLoadingEnemies)
				LoadEnemies();

				//Player Movement

				//Force to move the player
				const float forceMagnitude = 0.5f;
				Engine::Vector2D force(0.0f, 0.0f);

				//Force for the monsters
				Engine::Vector2D monster_force(-0.1f, 0.0f);

				//Move the player
				if (Engine::Input::keyHandler.A.m_isDown)
				{
					force = Engine::Vector2D(-forceMagnitude, force.y());
				}

				if (Engine::Input::keyHandler.D.m_isDown)
				{
					force = Engine::Vector2D(forceMagnitude, force.y());
				}

				if (Engine::Input::keyHandler.W.m_isDown)
				{
					force = Engine::Vector2D(0.0f, forceMagnitude);
				}

				if (Engine::Input::keyHandler.S.m_isDown)
				{
					force = Engine::Vector2D(0.0f, -forceMagnitude);
				}

				bulletForce = Engine::Vector2D(0.0f, 0.0f);
				//Fire a bullet
				if (Engine::Input::keyHandler.H.m_isDown && !firedBullet)
				{
					bullets[0]->getGObject()->SetVelocity(Engine::Vector2D(0.0f, 0.0f));
					bullets[0]->getGObject()->SetPosition(Engine::Vector2D(playerPosition.x(), playerPosition.y() + 50.0f));
					bulletForce = Engine::Vector2D(bulletForceMagnitude, 0.0f);
					firedBullet = true;
				}
				

				//Show exit the game the player won
				if (playerScore > 2000)
				{
					bQuit = true;
				}

				////Show exit the game the player lost
				if (playerHealth <= 0)
				{
					bQuit = true;
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
					//Check collision for actors
					if (actorsInScene.size() > 1)
					{

						for (size_t i = 0; i < actorsInScene.size(); i++)
						{

							for (size_t j = i + 1; j < actorsInScene.size(); j++)
							{

								if (actorsInScene[i]->getType() == "Level" && actorsInScene[j]->getType() == "Level")
								{
									continue;
								}

								if (actorsInScene[i]->getType() == "Player" && actorsInScene[j]->getType() == "Projectile")
								{
									continue;
								}

								if (actorsInScene[i]->getType() == "Projectile" && actorsInScene[j]->getType() == "Player")
								{
									continue;
								}

								if (actorsInScene[i]->getType() == "Monster" && actorsInScene[j]->getType() == "Monster")
								{
									continue;
								}

								PROFILE_UNSCOPED("Engine::Collision::CheckCollisions");
								Engine::Collision::CheckCollisions(actorsInScene[i], actorsInScene[j], dt);
								PROFILE_SCOPE_END();
							}
						}
					}

					//Update the player movement
 					if (actorsInScene[i]->getType() == "Player")
					{
						actorsInScene[i]->getPhysics().Acquire()->Update(force, dt);
						playerPosition = actorsInScene[i]->getGObject()->GetPosition();
						
					}
					else if (actorsInScene[i]->getType() == "Monster")
					{
						actorsInScene[i]->getPhysics().Acquire()->Update(monster_force, dt);
					}
					else if (actorsInScene[i]->getType() == "Projectile")
					{
						//DEBUG_LOG_OUTPUT("Bullet force: x: %f, y: %f/n", bulletForce.x(), bulletForce.y());
						if(firedBullet)
						actorsInScene[i]->getPhysics().Acquire()->Update(bulletForce, dt);
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

void Game::LoadBullets()
{
	if (loadedBullets < maxNumberOfBullets) {

		//Get the processor instance
		Engine::ThreadedFileProcessor &Processor = Engine::ThreadedFileProcessor::GetInstance();

		Processor.AddToLoadQueue(*new Engine::ShowTask("..//data/Bullet.lua", "Bullet", actorsToAdd, actorMu));
	}

	loadedBullets++;

	if (bullets.size() == maxNumberOfBullets && !doneLoadingBullets)
	{

		//The second platform
		bullets[0]->getGObject()->SetPosition(Engine::Vector2D(-1100.0f, -2000.0f));

		doneLoadingBullets = true;
	}

}

void Game::LoadEnemies()
{
	if (numberOfEnemies < maxNumberOfEnemies) {

		//Get the processor instance
		Engine::ThreadedFileProcessor &Processor = Engine::ThreadedFileProcessor::GetInstance();

		Processor.AddToLoadQueue(*new Engine::ShowTask("..//data/Monster1.lua", "Monster1", actorsToAdd, actorMu));
	}

	numberOfEnemies++;

	if (enemies.size() == maxNumberOfEnemies && !doneLoadingEnemies)
	{

		
		enemies[0]->getGObject()->SetPosition(enemySpawnPositions[0]);
		enemies[1]->getGObject()->SetPosition(enemySpawnPositions[1]);
		enemies[2]->getGObject()->SetPosition(enemySpawnPositions[2]);

		doneLoadingEnemies = true;
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

		//Add the bullet to the vector of bullets
		if (temp->getType() == "Projectile")
		{
			bullets.push_back(temp);
		}
	
		//Add the enemy to the vector of enemies
		if (temp->getType() == "Monster")
		{
			enemies.push_back(temp);
		}
	}

	actorMu.Release();

}


void Game::OnCollision(const Engine::CollisionPair & i_Pair, const Engine::Vector3 & i_colNormal)
{
	actorMu.Acquire();

	//Check the pair for each case
	if (i_Pair.m_CollisionObjects[0].Acquire()->getType() == "Level" && i_Pair.m_CollisionObjects[1].Acquire()->getType() == "Projectile")
	{
		i_Pair.m_CollisionObjects[1].Acquire()->getGObject()->SetPosition(Engine::Vector2D(-1100.0f, -2000.0f));
		firedBullet = false;
		return;
	}
	else if (i_Pair.m_CollisionObjects[0].Acquire()->getType() == "Projectile" && i_Pair.m_CollisionObjects[1].Acquire()->getType() == "Level")
	{
		i_Pair.m_CollisionObjects[0].Acquire()->getGObject()->SetPosition(Engine::Vector2D(-1100.0f, -2000.0f));
		firedBullet = false;
		return;
	}
	else if (i_Pair.m_CollisionObjects[0].Acquire()->getType() == "Monster" && i_Pair.m_CollisionObjects[1].Acquire()->getType() == "Projectile")
	{
		i_Pair.m_CollisionObjects[0].Acquire()->getGObject()->SetPosition(enemySpawnPositions[rand() % 2]);
		i_Pair.m_CollisionObjects[1].Acquire()->getGObject()->SetPosition(Engine::Vector2D(-1100.0f, -2000.0f));
		playerScore += 10;
		firedBullet = false;
		return;
	}
	else if (i_Pair.m_CollisionObjects[0].Acquire()->getType() == "Projectile" && i_Pair.m_CollisionObjects[1].Acquire()->getType() == "Monster")
	{
		i_Pair.m_CollisionObjects[0].Acquire()->getGObject()->SetPosition(Engine::Vector2D(-1100.0f, -2000.0f));
		i_Pair.m_CollisionObjects[1].Acquire()->getGObject()->SetPosition(enemySpawnPositions[rand() % 2]);
		playerScore += 10;
		firedBullet = false;
		return;
	}

	else if (i_Pair.m_CollisionObjects[0].Acquire()->getType() == "Player" && i_Pair.m_CollisionObjects[1].Acquire()->getType() == "Monster")
	{
		playerHealth -= 20;

		return;
	}

	else if (i_Pair.m_CollisionObjects[0].Acquire()->getType() == "Monster" && i_Pair.m_CollisionObjects[1].Acquire()->getType() == "Player")
	{
		playerHealth -= 20;

		return;
	}


	else{
	//Objects A and B
	Engine::Vector2D velA = i_Pair.m_CollisionObjects[0].Acquire()->getGObject()->GetVelocity();
	Engine::Vector2D velB = i_Pair.m_CollisionObjects[1].Acquire()->getGObject()->GetVelocity();

	//The masses of the objects
	float massA = i_Pair.m_CollisionObjects[0].Acquire()->getPhysics().Acquire()->getMass();
	float massB = i_Pair.m_CollisionObjects[1].Acquire()->getPhysics().Acquire()->getMass();

	//Post collision velocities
	Engine::Vector2D velAPost = velA * ((massA - massB) / (massA + massB)) + velB * ((2.0f * massB) / (massA + massB));
	Engine::Vector2D velBPost = velB * ((massB - massA) / (massA + massB)) + velA * ((2.0f * massA) / (massA + massB));

	Engine::Vector2D colNormal = Engine::Vector2D(i_colNormal.x(), i_colNormal.y());

	if (!Engine::floatEpsilonEqual(i_colNormal.x(), 0.0f) || !Engine::floatEpsilonEqual(i_colNormal.y(), 0.0f))
		colNormal.normalize();

	//Post collision velocities with normal
	Engine::Vector2D velAPost2 = (colNormal * Engine::dot(velA, colNormal) * -2.0f) + velA;
	Engine::Vector2D velBPost2 = (colNormal * Engine::dot(velB, colNormal) * -2.0f) + velB;

	Engine::Vector2D resVelA = velAPost + velAPost2;
	Engine::Vector2D resVelB = velBPost + velBPost2;

	////Cap the velocities
	float maxVelocity = 17.0f;

	if (resVelA.x() >= maxVelocity)
		resVelA.x(maxVelocity);
	if (resVelA.x() <= -maxVelocity)
		resVelA.x(-maxVelocity);

	if (resVelA.y() >= maxVelocity)
		resVelA.y(maxVelocity);
	if (resVelA.y() <= -maxVelocity)
		resVelA.y(-maxVelocity);

	if (resVelB.x() >= maxVelocity)
		resVelB.x(maxVelocity);
	if (resVelB.x() <= -maxVelocity)
		resVelB.x(-maxVelocity);

	if (resVelB.y() >= maxVelocity)
		resVelB.y(maxVelocity);
	if (resVelB.y() <= -maxVelocity)
		resVelB.y(-maxVelocity);



		i_Pair.m_CollisionObjects[0].Acquire()->getGObject()->SetVelocity(resVelA);	
		i_Pair.m_CollisionObjects[1].Acquire()->getGObject()->SetVelocity(resVelB);
	

	
	}
	actorMu.Release();

}