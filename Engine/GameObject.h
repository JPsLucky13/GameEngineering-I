#pragma once
#include "Vector2D.h"
#include "Vector3.h"
#include <algorithm>
#include "EngineHandler.h"

namespace Engine {


	class GameObject
	{

	public:

		GameObject();
		~GameObject();

		//Initializer List
		GameObject(const Engine::Vector2D & i_InitialPosition) :
			m_Position(i_InitialPosition)
		{}

		//Copy Constructor
		GameObject(const GameObject & i_other);

		//Assignment operator
		GameObject & operator=(const GameObject & i_other);

		//Get and set position of the gameobject
		const Engine::Vector2D & GetPosition() const { return m_Position; }
		void SetPosition(const Engine::Vector2D & i_Position) { m_Position = i_Position; }

		//Get and set rotation
		const Engine::Vector3 & GetRotation() const { return m_Rotation; }
		void SetRotation(const Engine::Vector3 & i_Rotation) { m_Rotation = i_Rotation; }

		//Get and set velocity of the gameobject
		const Engine::Vector2D & GetVelocity() const { return m_Velocity; }
		void SetVelocity (const Engine::Vector2D & i_Velocity) { m_Velocity = i_Velocity; }

		void * operator new(size_t i_size);
		void operator delete(void * ptr);
	private:

		Engine::Vector2D m_Position;
		Engine::Vector2D m_Velocity;
		Engine::Vector3 m_Rotation;
	};

}

