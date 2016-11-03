#pragma once
#include <cstring>
#include "Vector2D.h"

class Monster {

private:

	char monsterName[30];

public:

	//The monster's position
	Engine::Vector2D monsterPosition;


	//Get the monster name
	inline const char* GetMonsterName()const;

	//Set the monster name
	inline void SetMonsterName(char* name);



};

#include "Monster-inl.h"