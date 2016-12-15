#pragma once
#include "Vector2D.h"
#include <stdio.h>
#include <conio.h>
#include <cstring>



#define BUFFER_SIZE 30

class PlayerController;

class Player{

	
	public:


		//Empty Constructor
		Player();

		~Player();

		//Get the player position
		Engine::Vector2D GetPosition() const;
		void SetController(PlayerController * c_Controller);
		PlayerController * GetPlayerController();

		//Get the player name
		inline const char* GetPlayerName()const;
		
		inline void SetPlayerName(const char* name);

		//The function to allow the player to choose their name
		void PlayerChooseName();

		//The function to display the player
		void DisplayPlayer() const;

		void UpdatePlayer();

		void PositionFormat();

	private:
		
		char playerName[BUFFER_SIZE];
		PlayerController * controller;
	};

#include "Player-inl.h"
