#pragma once
#include "IGameObjectController.h"
#include <stdlib.h>
#include <algorithm>
#include "GameObject.h"

class MonsterController : public Engine::IGameObjectController
{
public:

	//Constructor
	MonsterController();

	//Constructor with controller
	MonsterController(Engine::GameObject * i_GameObject);

	//Destructor
	~MonsterController();

	//Copy constructor
	MonsterController(const MonsterController & i_other);

	//Assignment operator
	MonsterController & operator=(const MonsterController & i_other);

	//Move Constructor
	MonsterController(MonsterController && i_other);

	//Move assignment operator
	MonsterController & operator=(MonsterController && i_other);


	void SetGameObject(Engine::GameObject * i_pObject) override { m_pObject = i_pObject; }
	Engine::GameObject * GetGameObject() override { return m_pObject; }

	void SetFocusObject(Engine::GameObject * i_pObject) { m_pFocus = i_pObject; }
	Engine::GameObject * GetFocusObject(){ return m_pFocus; }
	
	void UpdateGameObject() override;

	//Get position
	Engine::Vector2D GetPosition()  const { return m_pObject->GetPosition(); }
	void SetPosition(const Engine::Vector2D & i_Position) { m_pObject->SetPosition(i_Position);}

	void PositionFormat();
	Engine::Vector2D GetWanderDirection();

private:

	Engine::GameObject * m_pObject;
	Engine::GameObject * m_pFocus;
};