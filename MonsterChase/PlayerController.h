#pragma once
#include "IGameObjectController.h"
#include <conio.h>

class PlayerController : public IGameObjectController
{

public:

	PlayerController();

	~PlayerController();

	void SetGameObject(GameObject * i_pObject) override { m_pObject  = i_pObject; }
	void UpdateGameObject() override;
	Engine::Vector2D PlayerController::GetMovementDirectionFromUserInput();

	//Get Position
	Engine::Vector2D GetPosition() {return m_pObject->GetPosition();}
	void SetPosition(Engine::Vector2D & i_Position) { m_pObject->SetPosition(i_Position); }

	void PositionFormat();
private:
	GameObject * m_pObject;
};
