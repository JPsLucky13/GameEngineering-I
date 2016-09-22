// MonsterChase.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctime> //For calling a seed of random numbers
#include "Monster.h"
#include "Player.h"
//#include "Engine.h"



//The number of monsters
int monsterNumber = -1;

//Create the array of Monsters
Monster monsters[100];

//Create a player
Player player;

//The prototype of the monster naming method
void NameMonsters(int monsterNumber);

//The prototype of placing the monsters randomly on a grid
void PlaceMonsters(Monster monstersArray[]);

//The prototype to query the player's name
void PlayerChooseName();

//The prototype to display the monster positions
void DisplayMonsters();

//The prototype to display the player
void DisplayPlayer();

//The prototype to display the player movement options
char PlayerOptions();

//The prototype to move the monsters
void MoveMonsters();

//The prototype to check if the monsters are in the same space
void CheckMonsterPosition();


//The prototype to destroy the monster 
void DestroyMonster();

//The prototype to ask for the number of monsters
void AskforNumberOfMonsters();


int main()
{
	
	srand(time_t(0));

	//QUery the user for the number of monsters
	AskforNumberOfMonsters();

	//Query user for names of monsters
	NameMonsters(monsterNumber);

	//Place the monsters randomly
	PlaceMonsters(monsters);

	//Ask the player for their name
	PlayerChooseName();

	
	
	//Start of the main game loop

	//Show the monster and player positions
	do
	{
		MoveMonsters();
		DisplayMonsters();
		DisplayPlayer();
		CheckMonsterPosition();

	}while (PlayerOptions() != 'q');


    return 0;
}

//The definition of the NameMonsters Method
void NameMonsters(int monsterNumber)
{

	//Cycle through the monsters to assign them names
	for (int i = 0; i < monsterNumber; i++) {
		char name [10];
		printf("What name will you give monster %d ?:", i);
		scanf_s("%s",name,10);
		monsters[i].SetMonsterName(name);
		
	}

}

//The definition of placing the monsters
void PlaceMonsters(Monster monstersArray[])
{
	//Seed the random number
	//srand(time_t(NULL));

	//Cycle through the monsters and randomize their positions
	for (int i = 0; i < monsterNumber; i++) {
		monsters[i].monsterPosition = Engine::Vector2D((float)(rand() % 101), (float)(rand() % 101));
		
	}
	

}

//The definition of player choose name
void PlayerChooseName() {
	char  name [10];

	//Ask user to input their name
	printf("What is your name?:");
	scanf_s("%s", name,10);
	player.SetPlayerName(name);
	printf("\n");

}

//The definition to display monsters position
void DisplayMonsters() 
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



			printf("Monster %s is at position: [%s%d][%s%d]\n", monsters[i].GetMonsterName(), tempX,(int)monsters[i].monsterPosition.x(), tempY,(int)monsters[i].monsterPosition.y());
	}
}

//The definition to display player position
void DisplayPlayer()
{

	char * tempX = "\0";
	char * tempY = "\0";

	if (player.playerPosition.x() < 10.0f && player.playerPosition.x() > -10.0f)
	{
		tempX = "0";
	}

	if (player.playerPosition.y() < 10.0f && player.playerPosition.y() > -10.0f)
	{
		tempY = "0";
	}
		printf("%s is at position: [%s%d][%s%d]\n", player.GetPlayerName(),tempX,(int)player.playerPosition.x(),tempY, (int)player.playerPosition.y());
	
		
}

//The definition to display the player's options
char PlayerOptions()
{
	//char option[2];
	printf("Press A to move left, D to move right, W to move up or S to move Down.\nPress M to kill a monster or press Q to quit.");
	//scanf_s("%s", option,2);
	printf("\n\n");
	int input = _getch();

	//Move the player left
	if (input == 'a') {
		player.playerPosition = player.playerPosition - Engine::Vector2D(1.0f,0.0f);

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
	else if(input == 'm')
	{
		DestroyMonster();
	}


	return input;

}

void MoveMonsters()
{
	//Seed the random number
	//srand(time_t(NULL));

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

void CheckMonsterPosition() {

	for (int i = 0; i < monsterNumber -1; i++) {
		//First monster
		Engine::Vector2D tempMonster1 = monsters[i].monsterPosition;

		//Second monster
		Engine::Vector2D tempMonster2 = monsters[i+1].monsterPosition;

		//Check if a new monster has to be created
		if (tempMonster1 == tempMonster2)
		{
			
			char name[10];
			printf("A new Monster has appeared! How shall you name it?:");
			scanf_s("%s", name, 10);
			monsters[monsterNumber].SetMonsterName(name);
			monsters[monsterNumber].monsterPosition = Engine::Vector2D((float)(rand() % 101), (float)(rand() % 101));
			monsterNumber++; //Increase the maximum number of monsters
		}
		
	}

}

void DestroyMonster() {

	if(monsterNumber > 0)
	{
		monsters[monsterNumber].SetMonsterName("");
		monsters[monsterNumber].monsterPosition = Engine::Vector2D(0.0f, 0.0f);
		monsterNumber--;
	}
	else
	{
		printf("All monsters have been destroyed!!\n");
	}
	

}


void AskforNumberOfMonsters()
{

	//Ask user for the number of monsters

	while (monsterNumber < 0) {

		printf("How many monsters would you like to add?:");
		scanf_s("%d", &monsterNumber);

		//Check that the user has inputed a positive number of monsters
		if (monsterNumber < 0)
		{
			printf("Please enter a positive number!!\n");
		}


	}
}