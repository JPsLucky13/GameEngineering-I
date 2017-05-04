#include "Actor.h"
#include "NewDelete.h"
namespace Engine {

	Actor::Actor(char * i_name, const HashedString & i_type, const SmartPointer<GameObject>& i_pObject, const WeakPointer<PhysicsInfo>& i_pPhysics, const WeakPointer<Sprite>& i_pSprite):
		m_Name(_strdup(i_name)),
		m_Type(i_type),
		m_pObject (i_pObject),
		m_pPhysics(i_pPhysics),
		m_pSprite(i_pSprite)
	{
	}

	Actor::~Actor()
	{
		free(m_Name);
	}

	void * Actor::operator new(size_t i_size)
	{
		void * pReturn = nullptr;

		pReturn = GetBlockAllocator(nullptr)->_alloc(i_size,16);
		return pReturn;
	}

	void Actor::operator delete(void * ptr)
	{
		GetBlockAllocator(nullptr)->_free(ptr);
	}
		



}