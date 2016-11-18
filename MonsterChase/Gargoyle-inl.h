#include "Gargoyle.h"
#pragma once
inline const char * Gargoyle::GetGargoyleName() const
{
	return gargoyleName;
}

inline void Gargoyle::SetGargoyleName(char * name)
{
	strcpy_s(gargoyleName, name);
}
