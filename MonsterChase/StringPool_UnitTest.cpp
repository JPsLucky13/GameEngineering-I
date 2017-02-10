#include "StringPool.h"
#include "EngineHandler.h"
#include "BlockAllocator.h"
#include <assert.h>

void StringPool_UnitTest(Engine::BlockAllocator * i_pBlockAllocator)
{

	

	//Create the string pool
	Engine::StringPool * sp = new Engine::StringPool();
	size_t amountOfBytes = 1024;
	sp = sp->create(amountOfBytes, i_pBlockAllocator);

	const char * player = sp->add("Player");
	const char * player2 = sp->add("Player");
	assert(sp->find(player));

	const char * monster1 = sp->add("Monster");
	assert(sp->find(monster1));
	const char * monster2 = sp->add("Ogre");
	const char * monster3 = sp->add("Zebra");
	const char * monster4 = sp->add("Bobo");

	assert(sp->find(monster2));
	assert(sp->find(monster3));
	assert(sp->find(monster4));


}
