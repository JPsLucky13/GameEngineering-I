#pragma once
#include "IGameObjectController.h"
#include <stdlib.h>

class MonsterController : public IGameObjectController
{
public:

	MonsterController();

	~MonsterController();

	void SetGameObject(GameObject * i_pObject) override { m_pObject = i_pObject; }
	GameObject * GetGameObject() override { return m_pObject; }

	void SetFocusObject(GameObject * i_pObject) { m_pFocus = i_pObject; }
	void UpdateGameObject() override;

	//Get position
	Engine::Vector2D GetPosition()  const { return m_pObject->GetPosition(); }
	void SetPosition(const Engine::Vector2D & i_Position) { m_pObject->SetPosition(i_Position);}

	void PositionFormat();
	Engine::Vector2D GetWanderDirection();

private:

	GameObject * m_pObject;
	GameObject * m_pFocus;
};