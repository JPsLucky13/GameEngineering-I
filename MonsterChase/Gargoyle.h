#pragma once
#include <cstring>
#include "Vector2D.h"
#include "IGameObjectController.h"
#include "GargoyleController.h"
#define BUFFER_SIZE 30
class Gargoyle {

public:


	//Empty Constructor
	Gargoyle();

	//Destructor
	~Gargoyle();

	//Get the monster position
	Engine::Vector2D GetPosition() const { return controller->GetPosition(); }

	void SetController(GargoyleController * c_Controller) { controller = c_Controller; }
	GargoyleController * GetGargoyleController() { return controller; }
	

	//Set the position
	void SetPosition(const Engine::Vector2D & i_Position) { controller->SetPosition(i_Position); }

	//Get the monster name
	inline const char* GetGargoyleName()const;

	//Set the monster name
	inline void SetGargoyleName(char* name);

	void UpdateGargoyle() { controller->UpdateGameObject(); }

	void PositionFormat() { controller->PositionFormat(); }

private:

	char gargoyleName[BUFFER_SIZE];
	GargoyleController * controller;

};

#include "Gargoyle-inl.h"