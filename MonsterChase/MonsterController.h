#pragma once
#include "IGameObjectController.h"
#include "Vector2D.h"
#include <stdlib.h>

class MonsterController : public IGameObjectController
{
public:

	MonsterController();

	~MonsterController();

	void SetGameObject(GameObject * i_pObject) override;
	GameObject * GetGameObject() override;

	void SetFocusObject(GameObject * i_pObject);
	void UpdateGameObject() override;

	//Get position
	Engine::Vector2D GetPosition()  const;
	void SetPosition(const Engine::Vector2D & i_Position);

	void PositionFormat();
	Engine::Vector2D GetWanderDirection();

private:

	GameObject * m_pObject;
	GameObject * m_pFocus;
};