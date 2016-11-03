#pragma once

inline const char * Monster::GetMonsterName() const
{
	return monsterName;
}

inline void Monster::SetMonsterName(char * name)
{
	strcpy_s(monsterName, name);
}
