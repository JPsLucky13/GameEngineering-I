#include "GameObject.h"
#include "NewDelete.h"
namespace Engine {

	GameObject::GameObject() {
	}

	GameObject::~GameObject()
	{

	}

	GameObject::GameObject(const GameObject & i_other) :
		m_Position(i_other.m_Position),
		m_Velocity(i_other.m_Velocity),
		m_Rotation(i_other.m_Rotation)
	{
	}

	GameObject & GameObject::operator=(const GameObject & i_other)
	{
		m_Position = i_other.m_Position;
		m_Velocity = i_other.m_Velocity;
		m_Rotation = i_other.m_Rotation;
		return *this;
	}

	void * GameObject::operator new(size_t i_size)
	{
		void * pReturn = nullptr;

		pReturn = GetBlockAllocator(nullptr)->_alloc(i_size,16);
		return pReturn;
	}

	void GameObject::operator delete(void * ptr)
	{
		GetBlockAllocator(nullptr)->_free(ptr);
	}



}



