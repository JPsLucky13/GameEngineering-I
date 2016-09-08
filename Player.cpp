
#include "Player.h"
#include <cstring>

Player::Player() {
	PosX = 0;
	PosY = 0;
}


int Player::GetPlayerPositionX()
{
	return PosX;
}

int Player::GetPlayerPositionY()
{
	return PosY;
}

void Player::SetPlayerPositionX(int x)
{
	PosX = x;
}

void Player::SetPlayerPositionY(int y)
{
	PosY = y;
}

const char * Player::GetPlayerName() const
{
	return playerName;
}

void Player::SetPlayerName(char* name)
{
	strcpy_s(playerName,name);
}

