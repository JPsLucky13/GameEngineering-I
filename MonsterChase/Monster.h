#pragma once
#include <cstring>
#include "Vector2D.h"
#include "IGameObjectController.h"
#include "MonsterController.h"
#define BUFFER_SIZE 30
class Monster{

public:


	//Empty Constructor
	Monster();

	//Destructor
	~Monster();

	//Get the monster position
	Engine::Vector2D GetPosition() const { return controller->GetPosition();}

	void SetController(MonsterController * c_Controller) { controller = c_Controller; }
	MonsterController * GetMonsterController() { return controller; }

	//Set the position
	void SetPosition(const Engine::Vector2D & i_Position) { controller->SetPosition(i_Position);}

	//Get the monster name
	inline const char* GetMonsterName()const;

	//Set the monster name
	inline void SetMonsterName(char* name);

	void UpdateMonster() { controller->UpdateGameObject(); }

	void PositionFormat() { controller->PositionFormat(); }

private:

	char monsterName[BUFFER_SIZE];
	MonsterController * controller;

};

#include "Monster-inl.h"