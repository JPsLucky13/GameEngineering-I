#include "MonsterController.h"

MonsterController::MonsterController()
{
	m_pObject = new GameObject();
	m_pFocus = nullptr;

}

MonsterController::~MonsterController()
{
	
	delete(m_pObject);
	m_pObject = NULL;

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