#pragma once
#include <cstring>
#include "Vector2D.h"
#include "IGameObjectController.h"
#include "GargoyleController.h"
#include <algorithm>

class Gargoyle {

public:


	//Empty Constructor
	Gargoyle(const char * i_gargoyleName);

	//Destructor
	~Gargoyle();

	//Copy Constructor
	Gargoyle(const Gargoyle & i_other);

	//Assignment operator
	Gargoyle & operator=(const Gargoyle & i_other);

	//Move constructor
	Gargoyle(Gargoyle && i_other);

	//move assignment operator
	Gargoyle & operator=(Gargoyle && i_other);


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

	char  * gargoyleName;
	GargoyleController * controller;

};

#include "Gargoyle-inl.h"