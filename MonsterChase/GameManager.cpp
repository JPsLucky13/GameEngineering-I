#include "GameManager.h"
#include "Vector2D.h"
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
#define ASSERT(cond,message) void(0)

#endif



void GameManager::NameMonsters(int &monsterNumber)
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
		monsters[i].SetPosition(Engine::Vector2D((float)(rand() % 101), (float)(rand() % 101)));
		ASSERT(monsters[i].GetPosition().x() >= 0.0f && monsters[i].GetPosition().x() <= 100.0f, "Woops monster is out of bounds");
		ASSERT(monsters[i].GetPosition().y() >= 0.0f && monsters[i].GetPosition().y() <= 100.0f, "Woops monster is out of bounds");
	}
}

void GameManager::DisplayMonsters() const
{
	//Print the monster position and format the position
	for (int i = 0; i < monsterNumber; i++) {
		char * tempX = "\0";
		char * tempY = "\0";


		if (monsters[i].GetPosition().x() < 10.0f && monsters[i].GetPosition().x() > -10.0f)
		{
			tempX = "0";
		}

		if (monsters[i].GetPosition().y() < 10.0f && monsters[i].GetPosition().y() > -10.0f)
		{
			tempY = "0";
		}

		printf("Monster %s is at position: [%s%d][%s%d]\n", monsters[i].GetMonsterName(), tempX, static_cast<int>(monsters[i].GetPosition().x()), tempY, static_cast<int>(monsters[i].GetPosition().y()));
	}
}

void GameManager::ReadPlayerInput()
{
	
	printf("Press A to move left, D to move right, W to move up or S to move Down.\nPress M to kill a monster or press Q to quit.");
	printf("\n\n");

	player.UpdatePlayer();
	player.PositionFormat();
}

char GameManager::ReadAdditionalInput()
{
	int input = _getch();

	if (input == 'm')
	{
		DestroyMonster();
	}

	return input;
}





void GameManager::MoveMonsters()
{
	//Cycle through the monsters and randomize their positions
	for (int i = 0; i < monsterNumber; i++) {

		DEBUG_LOG_MESSAGE("The position of the monster is: X: %d, Y: %d\n", static_cast<int>(monsters[i].GetPosition().x()), static_cast<int>(monsters[i].GetPosition().y()));

		monsters[i].UpdateMonster();
		monsters[i].PositionFormat();

		DEBUG_LOG_MESSAGE("The position of the monster is: X: %d, Y: %d\n", static_cast<int>(monsters[i].GetPosition().x()), static_cast<int>(monsters[i].GetPosition().y()));

	}


}

void GameManager::CheckMonsterPosition()
{
	for (int i = 0; i < monsterNumber - 1; i++) {
		//First monster
		Engine::Vector2D tempMonster1 = monsters[i].GetPosition();

		//Second monster
		Engine::Vector2D tempMonster2 = monsters[i + 1].GetPosition();

		//Check if a new monster has to be created
		if (tempMonster1 == tempMonster2)
		{

			char name[10];
			printf("A new Monster has appeared! How shall you name it?:");
			scanf_s("%s", name, 10);
			monsters[monsterNumber].SetMonsterName(name);
			monsters[monsterNumber].SetPosition(Engine::Vector2D((float)(rand() % 101), (float)(rand() % 101)));
			monsterNumberAdd(); //Increase the maximum number of monsters
		}

	}
}

void GameManager::DestroyMonster()
{
	if (monsterNumber > 0)
	{
		DEBUG_LOG_MESSAGE("The number of monsters is: %d\n", monsterNumber);
		monsters[monsterNumber].SetMonsterName("");
		monsters[monsterNumber].SetPosition(Engine::Vector2D(0.0f, 0.0f));
		DEBUG_LOG_MESSAGE("The position of the monster is: X: %d, Y: %d\n", static_cast<int>(monsters[monsterNumber].GetPosition().x()), static_cast<int>(monsters[monsterNumber].GetPosition().y()));
		monsterNumberDecrease();
		DEBUG_LOG_MESSAGE("The number of monsters is: %d\n", monsterNumber);
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

void GameManager::UpdateGameManager()
{
	MoveMonsters();
	DisplayMonsters();
	player.DisplayPlayer();
	CheckMonsterPosition();
	ReadPlayerInput();
}
