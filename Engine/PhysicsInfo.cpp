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

		Vector2D velocity = m_pObject->GetVelocity() + Acceleration * i_dt;

		Vector2D coeff = velocity * -m_Drag;

		m_pObject->SetVelocity(velocity.isZero() ? velocity : velocity + coeff);
		m_pObject->SetPosition(m_pObject->GetPosition() + m_pObject->GetVelocity()  * i_dt);

//#ifdef _DEBUG
//		const size_t	lenBuffer = 200;
//		char			Buffer[lenBuffer];
//
//		sprintf_s(Buffer, lenBuffer, "DT %f  A:%f, %f  V:%f, %f  P:%f, %f\n", i_dt, 
//			Acceleration.x(), Acceleration.y(), 
//			m_pObject->GetVelocity().x(), m_pObject->GetVelocity().y(),
//			m_pObject->GetPosition().x(), m_pObject->GetPosition().y());
//		OutputDebugStringA(Buffer);
//#endif // __DEBUG
	}

	void PhysicsInfo::SetGameObject(GameObject * gameobject)
	{
		m_pObject = gameobject;
	}

}

