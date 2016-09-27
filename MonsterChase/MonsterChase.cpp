// MonsterChase.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <assert.h> 
#include <ctime> //For calling a seed of random numbers
#include "Monster.h"
#include "Player.h"
#include "GameManager.h"



int main()
{
	
	srand(time_t(0));

	//Create reference to a game manager object
	GameManager gameManager;

	//Initialize the game
	gameManager.InitializeGame();
	
	//Start of the main game loop
	do
	{
		gameManager.updateGameManager();

	}while (gameManager.PlayerOptions() != 'q');


    return 0;
}
