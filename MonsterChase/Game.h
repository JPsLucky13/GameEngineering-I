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



private:

	void Game::UpdateNewActors();

	Engine::Timer m_timer;
	static Engine::Physics * physics;
	static Engine::Renderer * renderer;
	static Engine::MessageSystem * messageSystem;
	bool m_renderSuccess = false;

	//Vectors of actors
	std::vector<Engine::SmartPointer<Engine::Actor>> actorsToAdd;
	std::vector<Engine::SmartPointer<Engine::Actor>> actorsInScene;

	//Mutex for actors
	Engine::Mutex actorMu;



};