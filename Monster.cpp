
#include "Monster.h"

int Monster::GetMonsterPositionX()
{
	return PosX;
}

int Monster::GetMonsterPositionY()
{
	return PosY;
}

void Monster::SetMonsterPositionX(int x)
{
	PosX = x;
}


void Monster::SetMonsterPositionY(int y)
{
	PosY = y;
}

const char * Monster::GetMonsterName() const
{
	return monsterName;
}

void Monster::SetMonsterName(char * name)
{
	strcpy_s(monsterName,name);
}
