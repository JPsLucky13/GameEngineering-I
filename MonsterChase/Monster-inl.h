#include "Monster.h"
#pragma once

inline const char * Monster::GetMonsterName() const
{
	return monsterName;
}

inline void Monster::SetMonsterName(char * name)
{
	if (monsterName)
	{
		free(monsterName);
	}
	monsterName = _strdup(name);
}
