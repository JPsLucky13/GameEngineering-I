#include "PhysicsInfo.h"

namespace Engine {

	PhysicsInfo::PhysicsInfo(GameObject* object, float mass, float drag)
	{
		m_pObject = object;
		m_Mass = mass;
		m_Drag = drag;
	}

	PhysicsInfo::~PhysicsInfo()
	{

	}

	void PhysicsInfo::Update(Vector2D & i_Force, float i_dt)
	{
		Vector2D Acceleration = i_Force / m_Mass;

		m_pObject->SetVelocity(m_pObject->GetVelocity() + Acceleration * i_dt);
		m_pObject->SetPosition(m_pObject->GetPosition() + m_pObject->GetVelocity()  * i_dt);
	}

	void PhysicsInfo::SetGameObject(GameObject * gameobject)
	{
		m_pObject = gameobject;
	}

}

