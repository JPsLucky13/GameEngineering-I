#pragma once
#include <cstring>
#include "Vector2D.h"

#define BUFFER_SIZE 30

class GargoyleController;

class Gargoyle {

public:


	//Empty Constructor
	Gargoyle();

	//Destructor
	~Gargoyle();

	//Get the monster position
	Engine::Vector2D GetPosition() const;

	void SetController(GargoyleController * c_Controller);
	GargoyleController * GetGargoyleController();
	

	//Set the position
	void SetPosition(const Engine::Vector2D & i_Position);

	//Get the monster name
	inline const char* GetGargoyleName()const;

	//Set the monster name
	inline void SetGargoyleName(char* name);

	void UpdateGargoyle();

	void PositionFormat();
private:

	char gargoyleName[BUFFER_SIZE];
	GargoyleController * controller;

};

#include "Gargoyle-inl.h"