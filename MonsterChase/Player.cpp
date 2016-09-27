
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

//The definition of player choose name
void Player::PlayerChooseName() {
	char  name[10];

	//Ask user to input their name
	printf("What is your name?:");
	scanf_s("%s", name, 10);
	SetPlayerName(name);
	printf("\n");

}


void Player::DisplayPlayer()
{
	char * tempX = "\0";
	char * tempY = "\0";

	if (playerPosition.x() < 10.0f && playerPosition.x() > -10.0f)
	{
		tempX = "0";
	}

	if (playerPosition.y() < 10.0f && playerPosition.y() > -10.0f)
	{
		tempY = "0";
	}
	printf("%s is at position: [%s%d][%s%d]\n", GetPlayerName(), tempX, (int)playerPosition.x(), tempY, (int)playerPosition.y());



}