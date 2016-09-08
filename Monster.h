#pragma once
#include <cstring>

class Monster {

private:


	int PosX;
	int PosY;

	char monsterName[30];

public:

	//Return the player's x and y positions
	int GetMonsterPositionX();
	int GetMonsterPositionY();



	//Set the value of the player's x and y positions
	void SetMonsterPositionX(int x);
	void SetMonsterPositionY(int y);

	//Get the monster name
	const char* GetMonsterName()const;

	//Set the monster name
	void SetMonsterName(char* name);



};