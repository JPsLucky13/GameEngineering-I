#pragma once
#include "Vector2D.h"
#include <stdio.h>
#include <conio.h>
#include "PlayerController.h"
#include <cstring>
	class Player{

	
	public:


		//Construtor with parameters
		Player(PlayerController * c_Controller);

		//Empty Constructor
		Player();

		~Player();

		//Get the player position
		Engine::Vector2D GetPosition() const{ return controller->GetPosition(); }

		void SetController(PlayerController * c_Controller) { controller = c_Controller;}


		//Get the player name
		inline const char* GetPlayerName()const;
		
		inline void SetPlayerName(const char* name);

		//The function to allow the player to choose their name
		void PlayerChooseName();

		//The function to display the player
		void DisplayPlayer() const;

		void UpdatePlayer() { controller->UpdateGameObject(); }

		void PositionFormat() { controller->PositionFormat(); }

	private:

		char playerName[30];
		PlayerController * controller;
	};

#include "Player-inl.h"
