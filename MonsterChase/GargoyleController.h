#pragma once

#include "IGameObjectController.h"
#include <stdlib.h>
#include <algorithm>

class GargoyleController : public IGameObjectController
{
public:

	GargoyleController();

	//Constructor with controller
	GargoyleController(GameObject * i_GameObject);

	~GargoyleController();

	//Copy Constructor
	GargoyleController(const GargoyleController & i_other);

	//Assignment operator
	GargoyleController & operator=(const GargoyleController & i_other);

	//Move constructor
	GargoyleController(GargoyleController && i_other);

	//Move assignment operator
	GargoyleController & operator=(GargoyleController && i_other);



	void SetGameObject(GameObject * i_pObject) override { m_pObject = i_pObject; }
	GameObject * GetGameObject() override { return m_pObject; }

	void SetFocusObject(GameObject * i_pObject) { m_pFocus = i_pObject; }
	GameObject * GetFocusObject() { return m_pFocus; }

	void UpdateGameObject() override;

	//Get position
	Engine::Vector2D GetPosition()  const { return m_pObject->GetPosition(); }
	void SetPosition(const Engine::Vector2D & i_Position) { m_pObject->SetPosition(i_Position); }

	void PositionFormat();
	Engine::Vector2D GetWanderDirection();

private:

	GameObject * m_pObject;
	GameObject * m_pFocus;
};