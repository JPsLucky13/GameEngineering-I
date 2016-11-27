#pragma once
#include <stdio.h>
#include "Monster.h"
#include "Player.h"
#include "Gargoyle.h"

#define ARRAY_MONST_SIZE 10
#define ARRAY_GAR_SIZE 10
#define NEG_ONE -1
class GameManager {

private:

	//The number of monsters
	int monsterNumber = NEG_ONE;

	//The number of gargoyles
	int gargoyleNumber = NEG_ONE;

	//Create the array of Monsters
	Monster monsters[ARRAY_MONST_SIZE];

	//Create the array of Gargoyles
	Gargoyle gargoyles[ARRAY_GAR_SIZE];

	//Create a player
	Player player;

public:


	//adder
	inline void monsterNumberAdd();
	//substract
	inline void monsterNumberDecrease();

	//adder
	inline void gargoyleNumberAdd();
	//substract
	inline void gargoyleNumberDecrease();

	inline Player GetPlayer() const { return player; }


	//The prototype of the monster naming method
	void NameMonsters(int &monsterNumber);


	//The prototype of the monster naming method
	void NameGargoyles(int &gargoyleNumber);


	//The prototype of placing the monsters randomly on a grid
	void PlaceMonsters();

	//The prototype of placing the gargoyles randomly on a grid
	void PlaceGargoyles();

	//The prototype to display the monster positions
	void DisplayMonsters() const;

	//The prototype to display the monster positions
	void DisplayGargoyles() const;

	//The prototype to display the player movement options
	void ReadPlayerInput();

	//The prototype for additional game inputs
	char ReadAdditionalInput();

	//The prototype to move the monsters
	void MoveMonsters();

	//The prototype to move the monsters
	void MoveGargoyles();

	//The prototype to check if the monsters are in the same space
	void CheckMonsterPosition();

	//The prototype to check if the monsters are in the same space
	void CheckGargoylePosition();

	//The prototype to destroy the monster 
	void DestroyMonster();

	//The prototype to destroy the monster 
	void DestroyGargoyle();

	//The prototype to ask for the number of monsters
	void AskforNumberOfMonsters();

	//The prototype to ask for the number of monsters
	void AskforNumberOfGargoyles();

	//The prototype to ask for the number of monsters
	void InitializeGame();

	void UpdateGameManager();
};

#include "GameManager-inl.h"