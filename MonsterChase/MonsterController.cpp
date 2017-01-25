#include "MonsterController.h"


MonsterController::MonsterController()
{
	m_pObject = new Engine::GameObject();
	m_pFocus = nullptr;

}

MonsterController::MonsterController(Engine::GameObject * i_GameObject)
{
	m_pObject = new Engine::GameObject();
	m_pObject->SetPosition(i_GameObject->GetPosition());
	m_pFocus = nullptr;

}

MonsterController::~MonsterController()
{
	if (m_pObject)
	{
	delete(m_pObject);
	m_pObject = NULL;
	}

}

MonsterController::MonsterController(const MonsterController & i_other) :
	m_pObject(new Engine::GameObject()),
	m_pFocus(i_other.m_pFocus)
{
	m_pObject->SetPosition(i_other.m_pObject->GetPosition());

}

MonsterController & MonsterController::operator=(const MonsterController & i_other)
{
	if (m_pObject) {
		delete m_pObject;
	}

	m_pObject = new Engine::GameObject();

	m_pObject->SetPosition(i_other.m_pObject->GetPosition());
	m_pFocus = i_other.m_pFocus;

	return *this;
}

MonsterController::MonsterController(MonsterController && i_other):
	m_pObject(i_other.m_pObject),
	m_pFocus(i_other.m_pFocus)
{
	i_other.m_pObject = nullptr;
	i_other.m_pFocus = nullptr;

}

MonsterController & MonsterController::operator=(MonsterController && i_other)
{
	std::swap(m_pObject, i_other.m_pObject);
	std::swap(m_pFocus, i_other.m_pFocus);

	return *this;

}


void MonsterController::UpdateGameObject()
{
	Engine::Vector2D Direction;
	if (m_pFocus) {

		Direction = m_pFocus->GetPosition() - m_pObject->GetPosition();
		if (m_pFocus->GetPosition() != m_pObject->GetPosition()) {
			Direction = Direction.normalize();
		}
		
	}
	else
	{
		Direction = GetWanderDirection();
	}
	m_pObject->SetPosition(m_pObject->GetPosition() + Direction);
}


Engine::Vector2D MonsterController::GetWanderDirection()
{
	return Engine::Vector2D((float)(rand() % 3) - 1, (float)(rand() % 3) - 1);
}

void MonsterController::PositionFormat()
{
	//Restrict the player movement to no go over 0
	if (m_pObject->GetPosition().x() < 0.0f)
		m_pObject->SetPosition(Engine::Vector2D(0.0f, m_pObject->GetPosition().y()));



	//Restrict the player movement to no go over 100
	if (m_pObject->GetPosition().x() > 100.0f)
		m_pObject->SetPosition(Engine::Vector2D(100.0f, m_pObject->GetPosition().y()));



	//Restrict the player movement to no go over 100
	if (m_pObject->GetPosition().y() > 100.0f)
		m_pObject->SetPosition(Engine::Vector2D(m_pObject->GetPosition().x(), 100.0f));



	//Restrict the player movement to no go over 100
	if (m_pObject->GetPosition().y() < 0.0f)
		m_pObject->SetPosition(Engine::Vector2D(m_pObject->GetPosition().x(), 0.0f));

}