
#include "Monster.h"
#include "MonsterController.h"

Monster::Monster() {
	controller = new MonsterController();
}

Monster::~Monster() {
	delete(controller);
	controller = NULL;
}


//Get the monster position
Engine::Vector2D Monster::GetPosition() const { return controller->GetPosition(); }

void Monster::SetController(MonsterController * c_Controller) { controller = c_Controller; }

MonsterController * Monster::GetMonsterController() { return controller; }

//Set the position
void Monster::SetPosition(const Engine::Vector2D & i_Position) { controller->SetPosition(i_Position); }

void Monster::UpdateMonster() { controller->UpdateGameObject(); }

void Monster::PositionFormat() { controller->PositionFormat(); }