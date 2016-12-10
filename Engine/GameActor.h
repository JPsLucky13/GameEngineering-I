#pragma once
#include "Vector2D.h"


namespace Engine{


class GameActor
{

public:
	//Get / Set the current position
	Engine::Vector2D GetPosition() const { return m_Position; }
	Engine::Vector2D SetPostion(Engine::Vector2D & i_Position) { m_Position = i_Position; }


private:
	Engine::Vector2D m_Position;

};

}