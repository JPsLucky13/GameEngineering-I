#pragma once


class Player{

private: 
	
	
	int PosX;
	int PosY;
	
	char playerName[30];

public:

	

	//Constructor
	Player();

	//Return the player's x and y positions
	int GetPlayerPositionX();
	int GetPlayerPositionY();

	

	//Set the value of the player's x and y positions
	void SetPlayerPositionX(int x);
	void SetPlayerPositionY(int y);

	//Get the player name
	const char* GetPlayerName()const;
	void SetPlayerName(char* name);
};