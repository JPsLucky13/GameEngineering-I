#include "GargoyleController.h"

GargoyleController::GargoyleController()
{
	m_pObject = new GameObject();
	m_pFocus = new GameObject();

}

GargoyleController::~GargoyleController()
{

	delete(m_pObject);
	delete(m_pFocus);
	m_pObject = NULL;
	m_pFocus = NULL;

}


void GargoyleController::UpdateGameObject()
{
	Engine::Vector2D Direction;
	if (m_pFocus) {

		Direction = m_pFocus->GetPosition() - m_pObject->GetPosition();
		Direction = Direction.normalize();
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
	//Restrict the monster movement to a 100 * 100 grind
	if (m_pObject->GetPosition().x() < 0.0f) {
		m_pObject->GetPosition().x(0.0f);
	}

	if (m_pObject->GetPosition().y() < 0.0f) {
		m_pObject->GetPosition().y(0.0f);
	}

	if (m_pObject->GetPosition().x() > 100.0f) {
		m_pObject->GetPosition().x(100.0f);
	}

	if (m_pObject->GetPosition().y() > 100.0f) {
		m_pObject->GetPosition().y(100.0f);
	}

}