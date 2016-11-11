#include "PlayerController.h"

PlayerController::PlayerController()
{
	m_pObject = new GameObject();
}

PlayerController::~PlayerController()
{
	
	delete(m_pObject);
	m_pObject = NULL;

}

void PlayerController::UpdateGameObject()
{
	if (m_pObject)
	{
		Engine::Vector2D Direction = GetMovementDirectionFromUserInput();
		m_pObject->SetPosition(m_pObject->GetPosition() + Direction);
	}
}

Engine::Vector2D PlayerController::GetMovementDirectionFromUserInput()
{
	int input = _getch();

	//Move the player left
	if (input == 'a') {

		return Engine::Vector2D(-1.0f, 0.0f);
	}

	//Move the player right
	else if (input == 'd')
	{
		return Engine::Vector2D(1.0f, 0.0f);
	}

	//Move the player up
	else if (input == 'w')
	{
		return Engine::Vector2D(0.0f, 1.0f);
	}

	//Move the player down
	else if (input == 's')
	{
		return Engine::Vector2D(0.0f, -1.0f);
	}

	else {
		return m_pObject->GetPosition();
	}

}

void PlayerController::PositionFormat()
{

	//Restrict the player movement to no go over 0
	if (m_pObject->GetPosition().x() < 0.0f)
		m_pObject->GetPosition().x(0.0f);



	//Restrict the player movement to no go over 100
	if (m_pObject->GetPosition().x() > 100.0f)
		m_pObject->GetPosition().x(100.0f);




	//Restrict the player movement to no go over 100
	if (m_pObject->GetPosition().y() > 100.0f)
		m_pObject->GetPosition().y(100.0f);



	//Restrict the player movement to no go over 100
	if (m_pObject->GetPosition().y() < 0.0f)
		m_pObject->GetPosition().y(0.0f);

}