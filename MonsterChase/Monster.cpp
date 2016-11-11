
#include "Monster.h"

Monster::Monster() {
	controller = new MonsterController();
}

Monster::~Monster() {
	delete(controller);
	controller = NULL;
}
