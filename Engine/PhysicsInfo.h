#pragma once
#include "GameObject.h"

namespace Engine
{
	class PhysicsInfo
	{

	public:
		PhysicsInfo(GameObject* object,float m_Mass,float m_Drag);
		~PhysicsInfo();

		//Updates the physics of the gameobject
		void Update(const Vector2D & i_Force, float i_dt);

		void SetGameObject(GameObject * gameobject);

	private:
		GameObject * m_pObject;
		float m_Mass;
		float m_Drag;
	};



}

