#pragma once
#include "PhysicsInfo.h"
#include <stdio.h>
#include "GLib.h"
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

	void PhysicsInfo::Update(const Vector2D& i_Force, float i_dt)
	{
		Vector2D Acceleration = i_Force / m_Mass;

		m_pObject->SetVelocity(m_pObject->GetVelocity() + Acceleration * i_dt);
		m_pObject->SetPosition(m_pObject->GetPosition() + m_pObject->GetVelocity()  * i_dt);

#ifdef _DEBUG
		const size_t	lenBuffer = 200;
		char			Buffer[lenBuffer];

		sprintf_s(Buffer, lenBuffer, "Zero Position x %f y %f", m_pObject->GetVelocity().x(), m_pObject->GetVelocity().y());
		OutputDebugStringA(Buffer);
#endif // __DEBUG


	}

	void PhysicsInfo::SetGameObject(GameObject * gameobject)
	{
		m_pObject = gameobject;
	}

}

