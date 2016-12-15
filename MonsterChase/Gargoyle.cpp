
#include "Gargoyle.h"
#include "GargoyleController.h"

Gargoyle::Gargoyle() {
	controller = new GargoyleController();
}

Gargoyle::~Gargoyle() {
	delete(controller);
	controller = NULL;
}

//Get the monster position
Engine::Vector2D Gargoyle::GetPosition() const { return controller->GetPosition(); }

void Gargoyle::SetController(GargoyleController * c_Controller) { controller = c_Controller; }

GargoyleController * Gargoyle::GetGargoyleController() { return controller; }


//Set the position
void Gargoyle::SetPosition(const Engine::Vector2D & i_Position) { controller->SetPosition(i_Position); }

void Gargoyle::UpdateGargoyle() { controller->UpdateGameObject(); }

void Gargoyle::PositionFormat() { controller->PositionFormat(); }