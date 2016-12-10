
#include "Vector2D.h"


void MonsterChase_UnitTest() {

	//Create two vectors
	const Engine::Vector2D one(1.0f,3.0f);
	const Engine::Vector2D two(1.0f,2.0f);
	Engine::Vector2D result;

	//Test the addition
	result = two + one;

	//Test the substraction
	result = one - two;

	//Test the comparison
	bool equal = false;

	if (one == two)
		equal = true;
	else
		equal = false;
	

	//Illegal operations due to const
	//one(1.0f,2.0f);

	//one = one + two;
	//one = one - two;


}