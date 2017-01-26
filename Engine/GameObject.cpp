#include "GameObject.h"
namespace Engine {

	GameObject::GameObject() {
		m_Position = Engine::Vector2D(0.0f, 0.0f);
		m_Velocity = Engine::Vector2D(0.0f, 0.0f);
	}

	GameObject::GameObject(const GameObject & i_other) :
		m_Position(i_other.m_Position)
	{
	}

	GameObject & GameObject::operator=(const GameObject & i_other)
	{
		m_Position = i_other.m_Position;
		return *this;
	}



}



