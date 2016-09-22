#pragma once
#include "Vector2D.h"

	class Player {

	private:

		char playerName[30];

	public:

		//THe monster's position
		Engine::Vector2D playerPosition;


		//Get the player name
		const char* GetPlayerName()const;
		void SetPlayerName(char* name);
	};
