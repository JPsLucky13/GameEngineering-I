#pragma once
#include <cstring>
#include "Vector2D.h"

#define BUFFER_SIZE 30

class MonsterController;

class Monster{

public:


	//Empty Constructor
	Monster();

	//Destructor
	~Monster();

	//Get the monster position
	Engine::Vector2D GetPosition() const;

	void SetController(MonsterController * c_Controller);
	MonsterController * GetMonsterController();

	//Set the position
	void SetPosition(const Engine::Vector2D & i_Position);

	//Get the monster name
	inline const char* GetMonsterName()const;

	//Set the monster name
	inline void SetMonsterName(char* name);

	void UpdateMonster();

	void PositionFormat();

private:

	char monsterName[BUFFER_SIZE];
	MonsterController * controller;

};

#include "Monster-inl.h"