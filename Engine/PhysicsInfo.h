#pragma once
#include "GameObject.h"
#include "SmartPointer.h"
#include "WeakPointer.h"
namespace Engine
{
	class PhysicsInfo
	{

	public:
		//PhysicsInfo(const SmartPointer<GameObject>& object,float m_Mass,float m_Drag);
		PhysicsInfo::PhysicsInfo(const WeakPointer<GameObject>& object, float mass, float drag);
		~PhysicsInfo();

		//Updates the physics of the gameobject
		void Update(const Vector2D & i_Force, float i_dt);

		void SetGameObject(SmartPointer<GameObject> gameobject);

	private:
		WeakPointer<GameObject> m_pObject;
		float m_Mass;
		float m_Drag;
	};



}

