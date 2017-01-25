#pragma once
#include "Vector2D.h"
#include <stdio.h>
#include <conio.h>


class PlayerController;

class Player{

	
	public:


		//Empty Constructor
		Player();

		~Player();

		//Copy Constructor
		Player(const Player & i_other);

		//Assignment Operator
		Player & operator=(const Player & i_other);

		//Move Constructor
		Player(Player && i_other);

		//Move Assignment operator	
		Player & operator=(Player && i_other);


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
		
		char * playerName;
		PlayerController * controller;
	};

#include "Player-inl.h"
