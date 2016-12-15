#include "PlayerController.h"
#include "GameObject.h"

#define SPEED_MUL 1
#define MIN_POS 0.0f
#define MAX_POS 100.0f
#define MAX_RAND 3
#define UP Engine::Vector2D(0.0f,1.0f)
#define DOWN Engine::Vector2D(0.0f,-1.0f)
#define LEFT Engine::Vector2D(-1.0f,0.0f)
#define RIGHT Engine::Vector2D(1.0f,0.0f)
#define VECTOR_ZERO Engine::Vector2D(0.0f,0.0f)


PlayerController::PlayerController()
{
	m_pObject = new GameObject();
}

PlayerController::~PlayerController()
{
	
	delete(m_pObject);
	m_pObject = NULL;

}

void PlayerController::SetGameObject(GameObject * i_pObject){ m_pObject = i_pObject; }
GameObject * PlayerController::GetGameObject(){ return m_pObject; }

bool PlayerController::GetIsDestroyingMonster() { return isDestroyingMonster; }
void PlayerController::SetIsDestroyingMonster(const bool i_value) { isDestroyingMonster = i_value; }

bool PlayerController::GetIsQuittingGame() { return isQuittingGame; }
void PlayerController::SetIsQuittingGame(const bool i_value) { isQuittingGame = i_value; }


void PlayerController::UpdateGameObject()
{
	if (m_pObject)
	{
		Engine::Vector2D Direction = GetMovementDirectionFromUserInput();
		m_pObject->SetPosition(m_pObject->GetPosition() + Direction * SPEED_MUL);
	}
}

Engine::Vector2D PlayerController::GetMovementDirectionFromUserInput()
{
	int input = _getch();

	//Move the player left
	if (input == 'a') {

		return LEFT;
	}

	//Move the player right
	else if (input == 'd')
	{
		return RIGHT;
	}

	//Move the player up
	else if (input == 'w')
	{
		return UP;
	}

	//Move the player down
	else if (input == 's')
	{
		return DOWN;
	}

	else if(input == 'm'){
		isDestroyingMonster = true;
		return VECTOR_ZERO;
	}
	else if (input == 'q') {
		isQuittingGame = true;
		return VECTOR_ZERO;
	}
	else {
		return VECTOR_ZERO;
	}
}

//Get Position
Engine::Vector2D PlayerController::GetPosition() { return m_pObject->GetPosition(); }
void PlayerController::SetPosition(Engine::Vector2D & i_Position) { m_pObject->SetPosition(i_Position); }

void PlayerController::PositionFormat()
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