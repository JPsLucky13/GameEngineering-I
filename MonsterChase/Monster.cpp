
#include "Monster.h"

const char * Monster::GetMonsterName() const
{
	return monsterName;
}

void Monster::SetMonsterName(char * name)
{
	strcpy_s(monsterName,name);
}
