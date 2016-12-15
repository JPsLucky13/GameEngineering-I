#pragma once
#include "IGameObjectController.h"
#include "Vector2D.h"
#include <conio.h>

class PlayerController : public IGameObjectController
{

public:

	PlayerController();

	~PlayerController();

	void SetGameObject(GameObject * i_pObject) override;
	GameObject * GetGameObject() override;

	bool GetIsDestroyingMonster();
	void SetIsDestroyingMonster(const bool i_value);

	bool GetIsQuittingGame();
	void SetIsQuittingGame(const bool i_value);

	void UpdateGameObject() override;
	Engine::Vector2D PlayerController::GetMovementDirectionFromUserInput();

	//Get Position
	Engine::Vector2D GetPosition();
	void SetPosition(Engine::Vector2D & i_Position);

	void PositionFormat();
private:
	GameObject * m_pObject;
	bool isDestroyingMonster = false;
	bool isQuittingGame = false;
};
