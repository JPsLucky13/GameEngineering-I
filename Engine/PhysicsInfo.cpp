#pragma once
#include "PhysicsInfo.h"
#include <stdio.h>
namespace Engine {

	PhysicsInfo::PhysicsInfo(const WeakPointer<GameObject>& object, float mass, float drag) :
		m_pObject(object),
		m_Mass(mass),
		m_Drag(drag)
	{}




	PhysicsInfo::~PhysicsInfo()
	{
	}

	void PhysicsInfo::Update(const Vector2D& i_Force, float i_dt)
	{
		Vector2D Acceleration = i_Force / m_Mass;

		//Vector2D Gravity = Engine::Vector2D(0.0f,-0.05f);

		Vector2D velocity = m_pObject.Acquire()->GetVelocity()  + Acceleration * i_dt;

		Vector2D coeff = velocity * -m_Drag;

		m_pObject.Acquire()->SetVelocity(velocity.isZero() ? velocity : velocity + coeff);
		m_pObject.Acquire()->SetPosition(m_pObject.Acquire()->GetPosition() + m_pObject.Acquire()->GetVelocity()  * i_dt);
	}

	void PhysicsInfo::SetGameObject(WeakPointer<GameObject> gameobject)
	{
		m_pObject = gameobject;
	}

}

