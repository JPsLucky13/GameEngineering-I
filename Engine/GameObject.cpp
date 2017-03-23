#include "GameObject.h"
namespace Engine {

	GameObject::GameObject() {
		m_Position = Engine::Vector2D(0.0f, 0.0f);
		m_Rotation = Engine::Vector3(0.0f, 0.0f,0.0f);
		m_Velocity = Engine::Vector2D(0.0f, 0.0f);
	}

	GameObject::~GameObject()
	{

	}

	GameObject::GameObject(const GameObject & i_other) :
		m_Position(i_other.m_Position),
		m_Rotation(i_other.m_Rotation)
	{
	}

	GameObject & GameObject::operator=(const GameObject & i_other)
	{
		m_Position = i_other.m_Position;
		m_Rotation = i_other.m_Rotation;
		return *this;
	}



}



