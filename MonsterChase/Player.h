#pragma once
#include "Vector2D.h"
#include <stdio.h>
#include <cstring>

	class Player {

	private:

		char playerName[30];

	public:

		//The monster's position
		Engine::Vector2D playerPosition;

		//Get the player name
		inline const char* GetPlayerName()const;
		
		inline void SetPlayerName(const char* name);

		//The function to allow the player to choose their name
		void PlayerChooseName();

		//The function to display the player
		void DisplayPlayer();
	};

#include "Player-inl.h"
