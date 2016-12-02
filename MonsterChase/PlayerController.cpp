#include "PlayerController.h"

PlayerController::PlayerController()
{
	m_pObject = new GameObject();
}

PlayerController::PlayerController(GameObject * i_GameObject)
{
	m_pObject = new GameObject();
	m_pObject->SetPosition(i_GameObject->GetPosition());
}

PlayerController::~PlayerController()
{
	if (m_pObject)
	{
		delete(m_pObject);
		m_pObject = NULL;
	}
}

PlayerController::PlayerController(const PlayerController & i_other):
	m_pObject(new GameObject())
{
	m_pObject->SetPosition(i_other.m_pObject->GetPosition());

}

PlayerController & PlayerController::operator=(const PlayerController & i_other)
{
	if (m_pObject) {
		delete m_pObject;
	}

	m_pObject = new GameObject();

	m_pObject->SetPosition(i_other.m_pObject->GetPosition());

	return *this;
}

PlayerController::PlayerController(PlayerController && i_other):
	m_pObject(i_other.m_pObject)
{
	i_other.m_pObject = nullptr;

}

PlayerController & PlayerController::operator=(PlayerController && i_other)
{
	std::swap(m_pObject, i_other.m_pObject);
	return *this;
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

	else if(input == 'm'){
		isDestroyingMonster = true;
		return Engine::Vector2D(0.0f, 0.0f);
	}
	else if (input == 'q') {
		isQuittingGame = true;
		return Engine::Vector2D(0.0f, 0.0f);
	}
	else {
		return Engine::Vector2D(0.0f, 0.0f);
	}
}

void PlayerController::PositionFormat()
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
		m_pObject->SetPosition(Engine::Vector2D(m_pObject->GetPosition().x(),0.0f));

}