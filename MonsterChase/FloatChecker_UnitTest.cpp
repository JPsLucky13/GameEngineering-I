
#include "FloatCheck.h"
#include <assert.h>

void FloatChecker_UnitTest() {

	//Check for valid float
	bool test = Engine::IsNaN(nanf(""));
	assert(test);


	//Check for NaN
	bool test2 = Engine::IsNaN(1.0f);
	assert(test2);

	//Check with epsilon
	bool test3 = Engine::floatEpsilonEqual(5.0f, 5.0f);
	assert(test3);

	//Check with epsilon second test
	bool test4 = Engine::floatEpsilonEqual(5.0f, 3.0f);
	assert(test4);

}