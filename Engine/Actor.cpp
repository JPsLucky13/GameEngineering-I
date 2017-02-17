#include "Actor.h"

namespace Engine {

	Actor::Actor(const SmartPointer<GameObject>& i_pObject, const SmartPointer<PhysicsInfo>& i_pPhysics, const SmartPointer<Sprite>& i_pSprite):
		m_pObject (i_pObject),
		m_pPhysics(i_pPhysics),
		m_pSprite(i_pSprite)
	{
	}

	Actor::~Actor()
	{
	}
		



}