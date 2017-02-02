#pragma once
#include "GameObject.h"
#include "SmartPointer.h"
namespace Engine
{
	class PhysicsInfo
	{

	public:
		PhysicsInfo(const SmartPointer<GameObject>& object,float m_Mass,float m_Drag);
		~PhysicsInfo();

		//Updates the physics of the gameobject
		void Update(const Vector2D & i_Force, float i_dt);

		void SetGameObject(SmartPointer<GameObject> gameobject);

	private:
		SmartPointer<GameObject> m_pObject;
		float m_Mass;
		float m_Drag;
	};



}

