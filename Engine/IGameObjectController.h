#pragma once


namespace Engine{

class GameObject;

class IGameObjectController
{

public:
	virtual void SetGameObject(GameObject * i_pObject) = 0;
	virtual GameObject * GetGameObject() = 0;
	virtual void UpdateGameObject() = 0;


};

}