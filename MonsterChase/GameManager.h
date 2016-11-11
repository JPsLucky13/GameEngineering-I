#pragma once
#include <stdio.h>
#include "Monster.h"
#include "Player.h"

class GameManager {

private:

	//The number of monsters
	int monsterNumber = -1;

	//Create the array of Monsters
	Monster monsters[10];

	//Create a player
	Player player;

public:


	//adder
	inline void monsterNumberAdd();
	//substract
	inline void monsterNumberDecrease();

	inline Player GetPlayer() const { return player; }


	//The prototype of the monster naming method
	void NameMonsters(int &monsterNumber);

	//The prototype of placing the monsters randomly on a grid
	void PlaceMonsters();

	//The prototype to display the monster positions
	void DisplayMonsters() const;

	//The prototype to display the player movement options
	void ReadPlayerInput();

	//The prototype for additional game inputs
	char ReadAdditionalInput();

	//The prototype to move the monsters
	void MoveMonsters();

	//The prototype to check if the monsters are in the same space
	void CheckMonsterPosition();

	//The prototype to destroy the monster 
	void DestroyMonster();

	//The prototype to ask for the number of monsters
	void AskforNumberOfMonsters();

	//The prototype to ask for the number of monsters
	void InitializeGame();

	void UpdateGameManager();
};

#include "GameManager-inl.h"