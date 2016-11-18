#include "GargoyleController.h"

GargoyleController::GargoyleController()
{
	m_pObject = new GameObject();
	m_pFocus = m_pFocus = nullptr;

}

GargoyleController::~GargoyleController()
{

	delete(m_pObject);
	m_pObject = NULL;

}


void GargoyleController::UpdateGameObject()
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
	m_pObject->SetPosition(m_pObject->GetPosition() + Direction * 4);
}


Engine::Vector2D GargoyleController::GetWanderDirection()
{
	return Engine::Vector2D((float)(rand() % 3) - 1, (float)(rand() % 3) - 1);
}

void GargoyleController::PositionFormat()
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