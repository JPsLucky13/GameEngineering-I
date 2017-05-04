#pragma once
#include "WeakPointer.h"
#include "SmartPointer.h"
#include "PhysicsInfo.h"
#include "Sprite.h"
#include "HashedString.h"

namespace Engine {

	
	
	class Actor	
	{



	public :

		struct AABB
		{
			Vector2D center;
			Vector2D extents;
		};

		Actor(char * i_name, const HashedString & i_type,const SmartPointer<GameObject>& i_pObject, const WeakPointer<PhysicsInfo>& i_pPhysics, const WeakPointer<Sprite>& i_pSprite);
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

		char * getName()
		{
			return m_Name;
		}

		HashedString getType()
		{
			return m_Type;
		}

		AABB getBoundingBox()
		{
			return  m_boundingBox;
		}

		void setBoundingBox(Vector2D & i_center, Vector2D & i_extents)
		{
			m_boundingBox.center = i_center;
			m_boundingBox.extents = i_extents;
		}

		void * operator new(size_t i_size);
		void operator delete(void * ptr);


	private:
		char * m_Name;
		HashedString m_Type;
		SmartPointer<GameObject> m_pObject;
		WeakPointer<PhysicsInfo> m_pPhysics;
		WeakPointer<Sprite>  m_pSprite;
		AABB m_boundingBox;
	};



}
