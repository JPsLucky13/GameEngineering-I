#include "Gargoyle.h"
#pragma once
inline const char * Gargoyle::GetGargoyleName() const
{
	return gargoyleName;
}

inline void Gargoyle::SetGargoyleName(char * name)
{
	if (gargoyleName)
	{
		free(gargoyleName);
	}
	gargoyleName = _strdup(name);
}
