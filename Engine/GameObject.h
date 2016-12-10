#pragma once
#include "Vector2D.h"
#include <algorithm>

class GameObject
{

public:

	GameObject();


	//Initializer List
	GameObject(const Engine::Vector2D & i_InitialPosition) :
		m_Position(i_InitialPosition)
	{}

	//Copy Constructor
	GameObject(const GameObject & i_other);

	//Assignment operator
	GameObject & operator=(const GameObject & i_other);




	//Get and set position of the vector
	Engine::Vector2D GetPosition() const { return m_Position; }
	void SetPosition(const Engine::Vector2D & i_Position) { m_Position = i_Position; }

private:

	Engine::Vector2D m_Position;
};