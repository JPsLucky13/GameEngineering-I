#pragma once
#include "WeakPointer.h"
#include "SmartPointer.h"
#include "PhysicsInfo.h"
#include "Sprite.h"


namespace Engine {

	class Actor
	{
	public :
		Actor(const SmartPointer<GameObject>& i_pObject, const WeakPointer<PhysicsInfo>& i_pPhysics, const WeakPointer<Sprite>& i_pSprite);
		~Actor();

		SmartPointer<GameObject>& getGObject()
		{
			return m_pObject;
		}


		WeakPointer<PhysicsInfo>& getPhysics()
		{
			return m_pPhysics;
		}
		
		
		WeakPointer<Sprite>& getSprite() {
			return m_pSprite;
		}


	private:
		SmartPointer<GameObject> m_pObject;
		WeakPointer<PhysicsInfo> m_pPhysics;
		WeakPointer<Sprite>  m_pSprite;
	};



}
