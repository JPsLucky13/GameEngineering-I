
#include "Gargoyle.h"

Gargoyle::Gargoyle() {
	controller = new GargoyleController();
}

Gargoyle::~Gargoyle() {
	delete(controller);
	controller = NULL;
}
