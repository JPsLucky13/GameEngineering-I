// MonsterChase.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctime> //For calling a seed of random numbers
#include "Monster.h"
#include "Player.h"

//The number of monsters
int monsterNumber = 0;

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


int main()
{
	

	//Ask user for the number of monsters
	printf("How many monsters would you like to add?:");
	scanf_s("%d", &monsterNumber);

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
	srand(time(NULL));

	//Cycle through the monsters and randomize their positions
	for (int i = 0; i < monsterNumber; i++) {
		monsters[i].SetMonsterPositionX(rand() % 101);
		monsters[i].SetMonsterPositionY(rand() % 101);
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
		if ((monsters[i].GetMonsterPositionX() < 10 && monsters[i].GetMonsterPositionX() > -10) || (monsters[i].GetMonsterPositionY() < 10 && monsters[i].GetMonsterPositionY() > -10))
			printf("Monster %s is at position: [0%d][0%d]\n", monsters[i].GetMonsterName(), monsters[i].GetMonsterPositionX(), monsters[i].GetMonsterPositionY());
		else
			printf("Monster %s is at position: [%d][%d]\n", monsters[i].GetMonsterName(), monsters[i].GetMonsterPositionX(), monsters[i].GetMonsterPositionY());
	}
}

//The definition to display player position
void DisplayPlayer()
{
	//Print the player position and format the position
	if((player.GetPlayerPositionX() < 10 && player.GetPlayerPositionX() > -10)|| (player.GetPlayerPositionY() < 10 && player.GetPlayerPositionY() > -10))
		printf("%s is at position: [0%d][0%d]\n", player.GetPlayerName(), player.GetPlayerPositionX(), player.GetPlayerPositionY());
	else
		printf("%s is at position: [%d][%d]\n", player.GetPlayerName(), player.GetPlayerPositionX(), player.GetPlayerPositionY());
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
		player.SetPlayerPositionX(player.GetPlayerPositionX() - 1);

		//Restrict the player movement to no go over 0
		if (player.GetPlayerPositionX() < 0)
			player.SetPlayerPositionX(0);

	}
	//Move the player right
	else if (input == 'd')
	{
		player.SetPlayerPositionX(player.GetPlayerPositionX() + 1);

		//Restrict the player movement to no go over 100
		if (player.GetPlayerPositionX() > 100)
			player.SetPlayerPositionX(100);
	}

	//Move the player up
	else if (input == 'w')
	{
		player.SetPlayerPositionY(player.GetPlayerPositionY() + 1);

		//Restrict the player movement to no go over 100
		if (player.GetPlayerPositionY() > 100)
			player.SetPlayerPositionY(100);
	}

	//Move the player down
	else if (input == 's')
	{
		player.SetPlayerPositionY(player.GetPlayerPositionY() - 1);

		//Restrict the player movement to no go over 100
		if (player.GetPlayerPositionY() < 0)
			player.SetPlayerPositionY(0);
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
	srand(time(NULL));

	//Cycle through the monsters and randomize their positions
	for (int i = 0; i < monsterNumber; i++) {
		monsters[i].SetMonsterPositionX(monsters[i].GetMonsterPositionX() + (rand() % 3)-1);//Generates -1,0 or 1
		monsters[i].SetMonsterPositionY(monsters[i].GetMonsterPositionY() + (rand() % 3)-1);

		//Restrict the monster movement to a 100 * 100 grind
		if (monsters[i].GetMonsterPositionX() < 0) {
			monsters[i].SetMonsterPositionX(0);
		}

		if (monsters[i].GetMonsterPositionY() < 0) {
			monsters[i].SetMonsterPositionY(0);
		}

		if (monsters[i].GetMonsterPositionX() > 100) {
			monsters[i].SetMonsterPositionX(100);
		}

		if (monsters[i].GetMonsterPositionY() > 100) {
			monsters[i].SetMonsterPositionY(100);
		}

	}


}

void CheckMonsterPosition() {

	for (int i = 0; i < monsterNumber -1; i++) {
		//First monster
		int x1 = monsters[i].GetMonsterPositionX();
		int y1 = monsters[i].GetMonsterPositionY();

		//Second monster
		int x2 = monsters[i+1].GetMonsterPositionX();
		int y2 = monsters[i+1].GetMonsterPositionY();

		//Check if a new monster has to be created
		if (x1 == x2 && y1 == y2)
		{
			char name[10];
			printf("A new Monster has appeared! How shall you name it?:");
			scanf_s("%s", name, 10);
			monsterNumber++; //Increase the maximum number of monsters
			monsters[monsterNumber].SetMonsterName(name);
			monsters[monsterNumber].SetMonsterPositionX(rand() % 101);
			monsters[monsterNumber].SetMonsterPositionY(rand() % 101);
		}
		
	}

}

void DestroyMonster() {

	if(monsterNumber > 0)
	{
		monsters[monsterNumber].SetMonsterName("");
		monsters[monsterNumber].SetMonsterPositionX(0);
		monsters[monsterNumber].SetMonsterPositionY(0);
		monsterNumber--;
	}
	else
	{
		printf("All monsters have been destroyed!!\n");
	}
	

}