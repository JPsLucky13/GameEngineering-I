#pragma once
#include "Vector2D.h"
#include <stdio.h>
#include <conio.h>
#include "PlayerController.h"
#include <cstring>

#define BUFFER_SIZE 30

class Player{

	
	public:


		//Empty Constructor
		Player();

		~Player();

		//Get the player position
		Engine::Vector2D GetPosition() const{ return controller->GetPosition(); }

		void SetController(PlayerController * c_Controller) { controller = c_Controller;}
		PlayerController * GetPlayerController() { return controller; }


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
		
		char playerName[BUFFER_SIZE];
		PlayerController * controller;
	};

#include "Player-inl.h"
