
#include "Gargoyle.h"

Gargoyle::Gargoyle(const char * i_gargoyleName) {
	gargoyleName = _strdup(i_gargoyleName);
	controller = new GargoyleController();
}

Gargoyle::~Gargoyle() {

	if (gargoyleName)
	{
	free(gargoyleName);
	gargoyleName = NULL;
	}

	if (controller)
	{
	delete(controller);
	controller = NULL;
	}
}

Gargoyle::Gargoyle(const Gargoyle & i_other):
	gargoyleName(_strdup(i_other.gargoyleName ? i_other.gargoyleName : "Gargoyle")),
	controller(new GargoyleController(i_other.controller->GetGameObject()))
{
	controller->SetFocusObject(i_other.controller->GetFocusObject());
}

Gargoyle & Gargoyle::operator=(const Gargoyle & i_other)
{
	if (gargoyleName)
		free(gargoyleName);


	gargoyleName = _strdup(i_other.gargoyleName ? i_other.gargoyleName : "Gargoyle");


	if (controller)
	{
		delete controller;
	}
	controller = new GargoyleController(i_other.controller->GetGameObject());
	controller->SetFocusObject(i_other.controller->GetFocusObject());
	return *this;
}

Gargoyle::Gargoyle(Gargoyle && i_other):
	gargoyleName(i_other.gargoyleName),
	controller(i_other.controller)
{
	i_other.gargoyleName = nullptr;
	i_other.controller = nullptr;

}

Gargoyle & Gargoyle::operator=(Gargoyle && i_other)
{
	std::swap(gargoyleName, i_other.gargoyleName);
	std::swap(controller, i_other.controller);

	return *this;
}
