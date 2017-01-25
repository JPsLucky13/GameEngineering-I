#include "Player.h"
#pragma once
#include <stdlib.h>
#include <cstring>



inline const char * Player::GetPlayerName() const
{
	return playerName;
}


inline void Player::SetPlayerName(const char* name)
{
	if (playerName)
	{
		free(playerName);
	}
	playerName = _strdup(name);
}
