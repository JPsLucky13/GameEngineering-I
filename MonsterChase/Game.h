#pragma once
#include "MessageSystem.h"
#include "HashedString.h"
#include "Game.h"
#include "Physics.h"

#include "Renderer.h"
#include "Timer.h"
#include "Input.h"
#include <vector>
#include "SmartPointer.h"
#include "Actor.h"
#include "ThreadedFileProcessor.h"
#include "ShowTask.h"
#include "Collision.h"

class Game
{
public:

	Game();
	~Game();

	void InitializeGame(HINSTANCE i_hInstance, int i_nCmdShow);
	bool StartGameLoop();
	void LoadLevelPlatforms();
	void LoadBullets();
	void LoadEnemies();


private:

	void UpdateNewActors();
	void OnCollision(const Engine::CollisionPair & i_Pair, const Engine::Vector3 & i_colNormal);

	static Engine::Physics * physics;
	static Engine::Renderer * renderer;
	static Engine::MessageSystem * messageSystem;
	static Engine::Timer * timer;
	bool m_renderSuccess = false;

	//Vectors of actors
	std::vector<Engine::SmartPointer<Engine::Actor>> actorsToAdd;
	std::vector<Engine::SmartPointer<Engine::Actor>> actorsInScene;

	//Mutex for actors
	Engine::Mutex actorMu;

	//Player attributes
	int playerHealth = 100;
	int playerScore = 0;
	float playerDirection = 1.0f;
	Engine::Vector2D playerPosition;

	//The platforms in the level
	int numberOfPlatforms = 0;
	const int maxNumberOfPlatforms = 11;
	bool donePlacingPlatforms = false;
	std::vector<Engine::SmartPointer<Engine::Actor>> platforms;

	//The bullets the player can fire
	int numberOfBullets = 0;
	int loadedBullets = 0;
	bool doneLoadingBullets = false;
	bool firedBullet = false;
	const int maxNumberOfBullets = 1;
	float bulletForceMagnitude = 80.0f;
	Engine::Vector2D bulletForce;
	std::vector<Engine::SmartPointer<Engine::Actor>>  bullets;

	//The enemies in the level
	const int enemiesToKill = 10;
	int numberOfEnemies = 0;
	const int maxNumberOfEnemies = 3;
	bool doneLoadingEnemies = false;
	Engine::Vector2D enemySpawnPositions[3];
	std::vector<Engine::SmartPointer<Engine::Actor>>  enemies;

};