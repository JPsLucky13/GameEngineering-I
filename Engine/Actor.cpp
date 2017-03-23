#include "Actor.h"

namespace Engine {

	Actor::Actor(char * i_name, const SmartPointer<GameObject>& i_pObject, const WeakPointer<PhysicsInfo>& i_pPhysics, const WeakPointer<Sprite>& i_pSprite):
		m_Name(_strdup(i_name)),
		m_pObject (i_pObject),
		m_pPhysics(i_pPhysics),
		m_pSprite(i_pSprite)
	{
	}

	Actor::~Actor()
	{
		free(m_Name);
	}
		



}