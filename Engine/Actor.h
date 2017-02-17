#pragma once
#include "WeakPointer.h"
#include "SmartPointer.h"
#include "PhysicsInfo.h"
#include "Sprite.h"


namespace Engine {

	class Actor
	{
	public :
		Actor(const SmartPointer<GameObject>& i_pObject, const SmartPointer<PhysicsInfo>& i_pPhysics, const SmartPointer<Sprite>& i_pSprite);
		~Actor();

		SmartPointer<GameObject> getGObject()
		{
			return m_pObject;
		}


		SmartPointer<PhysicsInfo> getPhysics()
		{
			return m_pPhysics;
		}
		
		
		SmartPointer<Sprite> getSprite() {
			return m_pSprite;
		}


	private:
		SmartPointer<GameObject> m_pObject;
		SmartPointer<PhysicsInfo> m_pPhysics;
		SmartPointer<Sprite>  m_pSprite;
	};



}
