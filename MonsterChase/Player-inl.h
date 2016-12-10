#include "Player.h"
#pragma once




inline const char * Player::GetPlayerName() const
{
	return playerName;
}


inline void Player::SetPlayerName(const char* name)
{
	strcpy_s(playerName, name);
}
