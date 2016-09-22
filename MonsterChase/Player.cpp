
#include "Player.h"
#include <cstring>



const char * Player::GetPlayerName() const
{
	return playerName;
}

void Player::SetPlayerName(char* name)
{
	strcpy_s(playerName,name);
}

