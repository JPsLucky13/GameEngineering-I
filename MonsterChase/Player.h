#pragma once
#include "Vector2D.h"
#include <stdio.h>

	class Player {

	private:

		char playerName[30];

	public:

		//The monster's position
		Engine::Vector2D playerPosition;


		//Get the player name
		const char* GetPlayerName()const;
		
		void SetPlayerName(char* name);

		//The function to allow the player to choose their name
		void PlayerChooseName();


		//The function to display the player
		void DisplayPlayer();
	};


