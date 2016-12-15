#include "MonsterController.h"
#include "GameObject.h"

#define SPEED_MUL 1
#define MIN_POS 0.0f
#define MAX_POS 100.0f
#define MAX_RAND 3


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


void MonsterController::SetGameObject(GameObject * i_pObject){ m_pObject = i_pObject; }
GameObject * MonsterController::GetGameObject(){ return m_pObject; }

void MonsterController::SetFocusObject(GameObject * i_pObject) { m_pFocus = i_pObject; }

//Get position
Engine::Vector2D MonsterController::GetPosition()  const { return m_pObject->GetPosition(); }
void MonsterController::SetPosition(const Engine::Vector2D & i_Position) { m_pObject->SetPosition(i_Position); }


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
	m_pObject->SetPosition(m_pObject->GetPosition() + Direction * SPEED_MUL);
}


Engine::Vector2D MonsterController::GetWanderDirection()
{
	return Engine::Vector2D((float)(rand() % MAX_RAND) - 1, (float)(rand() % MAX_RAND) - 1);
}

void MonsterController::PositionFormat()
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

