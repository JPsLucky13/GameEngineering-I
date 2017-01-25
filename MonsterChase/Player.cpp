
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

Player::Player(const Player & i_other):
controller(new PlayerController(i_other.controller->GetGameObject()))
{
	controller->SetGameObject(i_other.controller->GetGameObject());
}

Player & Player::operator=(const Player & i_other)
{

	if (controller)
	{
		delete controller;
	}
	controller = new PlayerController(i_other.controller->GetGameObject());
	return *this;
}

Player::Player(Player && i_other):
	controller(i_other.controller)
{
	i_other.controller = nullptr;
}

Player & Player::operator=(Player && i_other)
{
	std::swap(controller, i_other.controller);
	return *this;
}

Engine::Vector2D Player::GetPosition() const
{
	return controller->GetPosition();
}

void Player::SetController(PlayerController * c_Controller)
{
	controller = c_Controller;
}

PlayerController * Player::GetPlayerController()
{
	return controller;
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
	char tempX = '\0';
	char tempY = '\0';

	if (GetPosition().x() < 10.0f && GetPosition().x() > -10.0f)
	{
		tempX = '0';
	}

	if (GetPosition().y() < 10.0f && GetPosition().y() > -10.0f)
	{
		tempY = '0';
	}
	printf("%s is at position: [%c%d][%c%d]\n", GetPlayerName(), tempX, (int)GetPosition().x(), tempY, (int)GetPosition().y());

}

void Player::UpdatePlayer()
{
	controller->UpdateGameObject();
}

void Player::PositionFormat()
{
	controller->PositionFormat();
}



