#include "GargoyleController.h"
#include "GameObject.h"

#define SPEED_MUL 4
#define MIN_POS 0.0f
#define MAX_POS 100.0f
#define MAX_RAND 3


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

void GargoyleController::SetGameObject(GameObject * i_pObject) { m_pObject = i_pObject; }
GameObject * GargoyleController::GetGameObject(){ return m_pObject; }

void GargoyleController::SetFocusObject(GameObject * i_pObject) { m_pFocus = i_pObject; }


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
	m_pObject->SetPosition(m_pObject->GetPosition() + Direction * SPEED_MUL);
}


Engine::Vector2D GargoyleController::GetPosition()  const { return m_pObject->GetPosition(); }
void GargoyleController::SetPosition(const Engine::Vector2D & i_Position) { m_pObject->SetPosition(i_Position); }

Engine::Vector2D GargoyleController::GetWanderDirection()
{
	return Engine::Vector2D((float)(rand() % MAX_RAND) - 1, (float)(rand() % MAX_RAND) - 1);
}

void GargoyleController::PositionFormat()
{
	//Restrict the player movement to no go over 0
	if (m_pObject->GetPosition().x() < MIN_POS)
		m_pObject->SetPosition(Engine::Vector2D(MIN_POS, m_pObject->GetPosition().y()));



	//Restrict the player movement to no go over 100
	if (m_pObject->GetPosition().x() > MAX_POS)
		m_pObject->SetPosition(Engine::Vector2D(MAX_POS, m_pObject->GetPosition().y()));



	//Restrict the player movement to no go over 100
	if (m_pObject->GetPosition().y() > MAX_POS)
		m_pObject->SetPosition(Engine::Vector2D(m_pObject->GetPosition().x(), MAX_POS));



	//Restrict the player movement to no go over 100
	if (m_pObject->GetPosition().y() < MIN_POS)
		m_pObject->SetPosition(Engine::Vector2D(m_pObject->GetPosition().x(), MIN_POS));

}