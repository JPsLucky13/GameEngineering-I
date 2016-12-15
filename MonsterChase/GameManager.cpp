#include "GameManager.h"
#include "Vector2D.h"
#include "Debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <assert.h>

#define ZERO 0
#define MAX_NAME_SIZE 10
#define MIN_POS 0.0f
#define MAX_POS 100.0f
#define MAX_MODULE_POS 101
#define POS_POSITIVE_TEN 10.0f
#define POS_NEGATIVE_TEN -10.0f
#define NEG_ONE -1


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
		char name[MAX_NAME_SIZE];
		printf("What name will you give monster %d ?:", i);
		scanf_s("%s", name, MAX_NAME_SIZE);
		monsters[i].SetMonsterName(name);
		monsters[i].GetMonsterController()->SetFocusObject(player.GetPlayerController()->GetGameObject());
	}

}

void GameManager::NameGargoyles(int &gargoyleNumber)
{
	//Cycle through the monsters to assign them names
	for (int i = 0; i < gargoyleNumber; i++) {
		char name[MAX_NAME_SIZE];
		printf("What name will you give gargoyle %d ?:", i);
		scanf_s("%s", name, MAX_NAME_SIZE);
		gargoyles[i].SetGargoyleName(name);
		gargoyles[i].GetGargoyleController()->SetFocusObject(player.GetPlayerController()->GetGameObject());
	}

}


void GameManager::PlaceMonsters()
{
	//Cycle through the monsters and randomize their positions
	for (int i = 0; i < monsterNumber; i++) {
		monsters[i].SetPosition(Engine::Vector2D((float)(rand() % MAX_MODULE_POS), (float)(rand() % MAX_MODULE_POS)));
		ASSERT(monsters[i].GetPosition().x() >= MIN_POS && monsters[i].GetPosition().x() <= MAX_POS, "Woops monster is out of bounds");
		ASSERT(monsters[i].GetPosition().y() >= MIN_POS && monsters[i].GetPosition().y() <= MAX_POS, "Woops monster is out of bounds");
	}
}

void GameManager::PlaceGargoyles()
{
	//Cycle through the monsters and randomize their positions
	for (int i = 0; i < gargoyleNumber; i++) {
		gargoyles[i].SetPosition(Engine::Vector2D((float)(rand() % MAX_MODULE_POS), (float)(rand() % MAX_MODULE_POS)));
		ASSERT(gargoyles[i].GetPosition().x() >= MIN_POS && gargoyles[i].GetPosition().x() <= MAX_POS, "Woops gargoyle is out of bounds");
		ASSERT(gargoyles[i].GetPosition().y() >= MIN_POS && gargoyles[i].GetPosition().y() <= MAX_POS, "Woops gargoyle is out of bounds");
	}
}


void GameManager::DisplayMonsters() const
{
	//Print the monster position and format the position
	for (int i = 0; i < monsterNumber; i++) {
		char * tempX = "\0";
		char * tempY = "\0";


		if (monsters[i].GetPosition().x() < POS_POSITIVE_TEN && monsters[i].GetPosition().x() > POS_NEGATIVE_TEN)
		{
			tempX = "0";
		}

		if (monsters[i].GetPosition().y() < POS_POSITIVE_TEN && monsters[i].GetPosition().y() > POS_NEGATIVE_TEN)
		{
			tempY = "0";
		}

		printf("Monster %s is at position: [%s%d][%s%d]\n", monsters[i].GetMonsterName(), tempX, static_cast<int>(monsters[i].GetPosition().x()), tempY, static_cast<int>(monsters[i].GetPosition().y()));
	}
}

void GameManager::DisplayGargoyles() const
{
	//Print the monster position and format the position
	for (int i = 0; i < gargoyleNumber; i++) {
		char * tempX = "\0";
		char * tempY = "\0";


		if (gargoyles[i].GetPosition().x() < POS_POSITIVE_TEN && gargoyles[i].GetPosition().x() > POS_NEGATIVE_TEN)
		{
			tempX = "0";
		}

		if (gargoyles[i].GetPosition().y() < POS_POSITIVE_TEN && gargoyles[i].GetPosition().y() > POS_NEGATIVE_TEN)
		{
			tempY = "0";
		}

		printf("Gargoyle %s is at position: [%s%d][%s%d]\n", gargoyles[i].GetGargoyleName(), tempX, static_cast<int>(gargoyles[i].GetPosition().x()), tempY, static_cast<int>(gargoyles[i].GetPosition().y()));
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

	if (player.GetPlayerController()->GetIsDestroyingMonster())
	{
		DestroyMonster();
		DestroyGargoyle();
		player.GetPlayerController()->SetIsDestroyingMonster(false);
		return 'm';
	}

	else if(player.GetPlayerController()->GetIsQuittingGame()){
		return 'q';
	}

	return ' ';
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

void GameManager::MoveGargoyles()
{
	//Cycle through the monsters and randomize their positions
	for (int i = 0; i < gargoyleNumber; i++) {

		DEBUG_LOG_MESSAGE("The position of the gargoyle is: X: %d, Y: %d\n", static_cast<int>(gargoyles[i].GetPosition().x()), static_cast<int>(gargoyles[i].GetPosition().y()));

		gargoyles[i].UpdateGargoyle();
		gargoyles[i].PositionFormat();

		DEBUG_LOG_MESSAGE("The position of the gargoyle is: X: %d, Y: %d\n", static_cast<int>(gargoyles[i].GetPosition().x()), static_cast<int>(gargoyles[i].GetPosition().y()));

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

			char name[MAX_NAME_SIZE];
			printf("A new Monster has appeared! How shall you name it?:");
			scanf_s("%s", name, MAX_NAME_SIZE);
			monsters[monsterNumber].SetMonsterName(name);
			monsters[monsterNumber].SetPosition(Engine::Vector2D((float)(rand() % MAX_MODULE_POS), (float)(rand() % MAX_MODULE_POS)));
			monsterNumberAdd(); //Increase the maximum number of monsters
		}

	}
}


void GameManager::CheckGargoylePosition()
{
	for (int i = 0; i < gargoyleNumber - 1; i++) {
		//First monster
		Engine::Vector2D tempGargoyle1 = gargoyles[i].GetPosition();

		//Second monster
		Engine::Vector2D tempGargoyle2 = gargoyles[i + 1].GetPosition();

		//Check if a new monster has to be created
		if (tempGargoyle1 == tempGargoyle2)
		{

			char name[MAX_NAME_SIZE];
			printf("A new Gargoyle has appeared! How shall you name it?:");
			scanf_s("%s", name, MAX_NAME_SIZE);
			gargoyles[gargoyleNumber].SetGargoyleName(name);
			gargoyles[gargoyleNumber].SetPosition(Engine::Vector2D((float)(rand() % MAX_MODULE_POS), (float)(rand() % MAX_MODULE_POS)));
			gargoyleNumberAdd(); //Increase the maximum number of monsters
		}

	}
}


void GameManager::DestroyMonster()
{
	if (monsterNumber > 0)
	{
		DEBUG_LOG_MESSAGE("The number of monsters is: %d\n", monsterNumber);
		monsters[monsterNumber].SetMonsterName("");
		monsters[monsterNumber].SetPosition(Engine::Vector2D(MIN_POS, MIN_POS));
		DEBUG_LOG_MESSAGE("The position of the monster is: X: %d, Y: %d\n", static_cast<int>(monsters[monsterNumber].GetPosition().x()), static_cast<int>(monsters[monsterNumber].GetPosition().y()));
		monsterNumberDecrease();
		DEBUG_LOG_MESSAGE("The number of monsters is: %d\n", monsterNumber);
	}
	else
	{
		printf("All monsters have been destroyed!!\n");
	}


}


void GameManager::DestroyGargoyle()
{
	if (gargoyleNumber >0)
	{
		DEBUG_LOG_MESSAGE("The number of gargoyles is: %d\n", gargoyleNumber);
		gargoyles[gargoyleNumber].SetGargoyleName("");
		gargoyles[gargoyleNumber].SetPosition(Engine::Vector2D(MIN_POS, MIN_POS));
		DEBUG_LOG_MESSAGE("The position of the gargoyle is: X: %d, Y: %d\n", static_cast<int>(gargoyles[gargoyleNumber].GetPosition().x()), static_cast<int>(gargoyles[gargoyleNumber].GetPosition().y()));
		gargoyleNumberDecrease();
		DEBUG_LOG_MESSAGE("The number of gargoyles is: %d\n", gargoyleNumber);
	}
	else
	{
		printf("All gargoyles have been destroyed!!\n");
	}


}



void GameManager::AskforNumberOfMonsters()
{
	//Ask user for the number of monsters

	while (monsterNumber < 0) {

		printf("How many monsters would you like to add?:");
		scanf_s("%zu", &monsterNumber);

		//Check that the user has inputed a positive number of monsters
		ASSERT(monsterNumber>0, "Woops monster number is not positive");

		DEBUG_LOG_MESSAGE("The number of monsters is: %d\n", monsterNumber);
	}
}


void GameManager::AskforNumberOfGargoyles()
{
	//Ask user for the number of gargoyles

	while (gargoyleNumber < 0) {

		printf("How many gargoyles would you like to add?:");
		scanf_s("%zu", &gargoyleNumber);

		//Check that the user has inputed a positive number of monsters
		ASSERT(gargoyleNumber>0, "Woops gargoyle number is not positive");

		DEBUG_LOG_MESSAGE("The number of gargoyles is: %d\n", gargoyleNumber);
	}
}


void GameManager::InitializeGame()
{
	//QUery the user for the number of monsters
	AskforNumberOfMonsters();

	//QUery the user for the number of gargoyles
	AskforNumberOfGargoyles();

	//Query user for names of monsters
	NameMonsters(monsterNumber);

	//Query user for names of gargoyles
	NameGargoyles(gargoyleNumber);

	//Place the monsters randomly
	PlaceMonsters();

	//Place the gargoyles randomly
	PlaceGargoyles();

	//Ask the player for their name
	player.PlayerChooseName();


}

void GameManager::UpdateGameManager()
{
	MoveMonsters();
	MoveGargoyles();
	DisplayMonsters();
	DisplayGargoyles();
	player.DisplayPlayer();
	CheckMonsterPosition();
	CheckGargoylePosition();
	ReadPlayerInput();
}
