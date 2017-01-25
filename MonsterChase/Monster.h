#pragma once
#include "Vector2D.h"

class MonsterController;

class Monster{

public:

	//Empty Constructor
	Monster();

	Monster(const char * i_monsterName);

	//Destructor
	~Monster();

	//Copy Constructor
	Monster(const Monster & i_other);

	//Assignment Operator
	Monster & operator=(const Monster & i_other);

	//Move Constructor
	Monster(Monster && i_other);

	//Move Assignment operator	
	Monster & operator=(Monster && i_other);

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

	char * monsterName;
	MonsterController * controller;

};

#include "Monster-inl.h"