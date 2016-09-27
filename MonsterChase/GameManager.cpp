#include "GameManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <assert.h>


#ifdef _DEBUG
#define DEBUG_LOG_MESSAGE(fmt,...) Engine::PrintDebugMessage(__FILE__,__FUNCTION__,__LINE__,fmt,__VA_ARGS__)
#define ASSERT(cond,message) assert((cond))
#else
#define DEBUG_LOG_MESSAGE(fmt,...) void(0)
#define ASSERT_MONSTER_NUMBER(cond,message) void (0)
#endif



void GameManager::NameMonsters(int monsterNumber)
{
	//Cycle through the monsters to assign them names
	for (int i = 0; i < monsterNumber; i++) {
		char name[10];
		printf("What name will you give monster %d ?:", i);
		scanf_s("%s", name, 10);
		monsters[i].SetMonsterName(name);
	}

}

void GameManager::PlaceMonsters()
{
	//Cycle through the monsters and randomize their positions
	for (int i = 0; i < monsterNumber; i++) {
		monsters[i].monsterPosition = Engine::Vector2D((float)(rand() % 101), (float)(rand() % 101));

	}
}

void GameManager::DisplayMonsters()
{
	//Print the monster position and format the position
	for (int i = 0; i < monsterNumber; i++) {
		char * tempX = "\0";
		char * tempY = "\0";


		if (monsters[i].monsterPosition.x() < 10.0f && monsters[i].monsterPosition.x() > -10.0f)
		{
			tempX = "0";
		}

		if (monsters[i].monsterPosition.y() < 10.0f && monsters[i].monsterPosition.y() > -10.0f)
		{
			tempY = "0";
		}



		printf("Monster %s is at position: [%s%d][%s%d]\n", monsters[i].GetMonsterName(), tempX, (int)monsters[i].monsterPosition.x(), tempY, (int)monsters[i].monsterPosition.y());
	}
}

char GameManager::PlayerOptions()
{
	//char option[2];
	printf("Press A to move left, D to move right, W to move up or S to move Down.\nPress M to kill a monster or press Q to quit.");
	//scanf_s("%s", option,2);
	printf("\n\n");
	int input = _getch();

	//Move the player left
	if (input == 'a') {
		player.playerPosition = player.playerPosition - Engine::Vector2D(1.0f, 0.0f);

		//Restrict the player movement to no go over 0
		if (player.playerPosition.x() < 0.0f)
			player.playerPosition.x(0.0f);

	}
	//Move the player right
	else if (input == 'd')
	{
		player.playerPosition = player.playerPosition + Engine::Vector2D(1.0f, 0.0f);

		//Restrict the player movement to no go over 100
		if (player.playerPosition.x() > 100.0f)
			player.playerPosition.x(100.0f);
	}

	//Move the player up
	else if (input == 'w')
	{
		player.playerPosition = player.playerPosition + Engine::Vector2D(0.0f, 1.0f);

		//Restrict the player movement to no go over 100
		if (player.playerPosition.y() > 100.0f)
			player.playerPosition.y(100.0f);
	}

	//Move the player down
	else if (input == 's')
	{
		player.playerPosition = player.playerPosition - Engine::Vector2D(0.0f, 1.0f);

		//Restrict the player movement to no go over 100
		if (player.playerPosition.y() < 0.0f)
			player.playerPosition.y(0.0f);
	}

	//Destroy a monster
	else if (input == 'm')
	{
		DestroyMonster();
	}


	return input;
}

void GameManager::MoveMonsters()
{
	//Cycle through the monsters and randomize their positions
	for (int i = 0; i < monsterNumber; i++) {

		Engine::Vector2D delta = Engine::Vector2D((float)(rand() % 3) - 1, (float)(rand() % 3) - 1);

		//printf("%s - %d  MONSTER:%f, %f\t\tDELTA:%f, %f\n", __FUNCTION__, __LINE__ , monsters[i].monsterPosition.x(), monsters[i].monsterPosition.y(), delta.x(), delta.y());
		monsters[i].monsterPosition = monsters[i].monsterPosition + delta;
		//printf("%s - %d  MONSTER:%f, %f\t\tDELTA:%f, %f\n", __FUNCTION__, __LINE__, monsters[i].monsterPosition.x(), monsters[i].monsterPosition.y(), delta.x(), delta.y());

		//Restrict the monster movement to a 100 * 100 grind
		if (monsters[i].monsterPosition.x() < 0.0f) {
			monsters[i].monsterPosition.x(0.0f);
		}

		if (monsters[i].monsterPosition.y() < 0.0f) {
			monsters[i].monsterPosition.y(0.0f);
		}

		if (monsters[i].monsterPosition.x() > 100.0f) {
			monsters[i].monsterPosition.x(100.0f);
		}

		if (monsters[i].monsterPosition.y() > 100.0f) {
			monsters[i].monsterPosition.y(100.0f);
		}

	}


}

void GameManager::CheckMonsterPosition()
{
	for (int i = 0; i < monsterNumber - 1; i++) {
		//First monster
		Engine::Vector2D tempMonster1 = monsters[i].monsterPosition;

		//Second monster
		Engine::Vector2D tempMonster2 = monsters[i + 1].monsterPosition;

		//Check if a new monster has to be created
		if (tempMonster1 == tempMonster2)
		{

			char name[10];
			printf("A new Monster has appeared! How shall you name it?:");
			scanf_s("%s", name, 10);
			monsters[monsterNumber].SetMonsterName(name);
			monsters[monsterNumber].monsterPosition = Engine::Vector2D((float)(rand() % 101), (float)(rand() % 101));
			monsterNumberAdd(); //Increase the maximum number of monsters
		}

	}
}

void GameManager::DestroyMonster()
{
	if (monsterNumber > 0)
	{
		monsters[monsterNumber].SetMonsterName("");
		monsters[monsterNumber].monsterPosition = Engine::Vector2D(0.0f, 0.0f);
		monsterNumberDecrease();
	}
	else
	{
		printf("All monsters have been destroyed!!\n");
	}


}

void GameManager::AskforNumberOfMonsters()
{
	//Ask user for the number of monsters

	while (monsterNumber < 0) {

		printf("How many monsters would you like to add?:");
		scanf_s("%d", &monsterNumber);

		//Check that the user has inputed a positive number of monsters
		ASSERT(monsterNumber>0, "Woops monster number is not positive");



		DEBUG_LOG_MESSAGE("The number of monsters is: %d\n", monsterNumber);
	}
}

void GameManager::InitializeGame()
{
	//QUery the user for the number of monsters
	AskforNumberOfMonsters();

	//Query user for names of monsters
	NameMonsters(monsterNumber);

	//Place the monsters randomly
	PlaceMonsters();

	//Ask the player for their name
	player.PlayerChooseName();


}

void GameManager::updateGameManager()
{
	MoveMonsters();
	DisplayMonsters();
	player.DisplayPlayer();
	CheckMonsterPosition();
}
