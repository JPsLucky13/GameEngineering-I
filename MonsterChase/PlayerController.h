#pragma once
#include "IGameObjectController.h"
#include <conio.h>
#include "Vector2D.h"
#include "GameObject.h"


class PlayerController : public Engine::IGameObjectController
{

public:

	PlayerController();

	//Constructor with controller
	PlayerController(Engine::GameObject * i_GameObject);

	~PlayerController();

	//Copy Constructor
	PlayerController(const PlayerController & i_other);

	//Assignment Operator
	PlayerController & operator=(const PlayerController & i_other);

	//Move Constructor
	PlayerController(PlayerController && i_other);

	//Move Assignment operator	
	PlayerController & operator=(PlayerController && i_other);



	void SetGameObject(Engine::GameObject * i_pObject) override { m_pObject  = i_pObject; }
	Engine::GameObject * GetGameObject() override { return m_pObject; }

	bool GetIsDestroyingMonster() { return isDestroyingMonster; }
	void SetIsDestroyingMonster(const bool i_value) { isDestroyingMonster = i_value; }

	bool GetIsQuittingGame() { return isQuittingGame; }
	void SetIsQuittingGame(const bool i_value) { isQuittingGame = i_value; }

	void UpdateGameObject() override;
	Engine::Vector2D PlayerController::GetMovementDirectionFromUserInput();

	//Get Position
	Engine::Vector2D GetPosition() {return m_pObject->GetPosition();}
	void SetPosition(Engine::Vector2D & i_Position) { m_pObject->SetPosition(i_Position); }

	void PositionFormat();
private:
	Engine::GameObject * m_pObject;
	bool isDestroyingMonster = false;
	bool isQuittingGame = false;
	
};
