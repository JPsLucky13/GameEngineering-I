
#include "Player.h"
#include "PlayerController.h"


Player::Player()
{
	controller = new PlayerController();
}

Player::~Player() {
	delete(controller);
	controller = NULL;
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


void Player::DisplayPlayer() const
{
	char * tempX = "\0";
	char * tempY = "\0";

	if (GetPosition().x() < 10.0f && GetPosition().x() > -10.0f)
	{
		tempX = "0";
	}

	if (GetPosition().y() < 10.0f && GetPosition().y() > -10.0f)
	{
		tempY = "0";
	}
	printf("%s is at position: [%s%d][%s%d]\n", GetPlayerName(), tempX, (int)GetPosition().x(), tempY, (int)GetPosition().y());

}


//Get the player position
Engine::Vector2D Player::GetPosition() const { return controller->GetPosition(); }

void Player::SetController(PlayerController * c_Controller) { controller = c_Controller; }
PlayerController * Player::GetPlayerController() { return controller; }

void Player::UpdatePlayer() { controller->UpdateGameObject(); }

void Player::PositionFormat() { controller->PositionFormat(); }