#include "FSAManager.h"
#include "NewDelete.h"



Engine::FSAManager::FSAManager()
{
}

Engine::FSAManager::~FSAManager()
{
}

void Engine::FSAManager::CreateFSAs(BlockAllocator * i_blockAllocator)
{
	//Initialize the sizes for the fixed sized block allocators
	//8 bytes
	FSASizes[0].sizeBlock = 8;
	FSASizes[0].numBlocks = 20;

	//16 bytes
	FSASizes[1].sizeBlock = 16;
	FSASizes[1].numBlocks = 20;

	//32 bytes
	FSASizes[2].sizeBlock = 32;
	FSASizes[2].numBlocks = 20;

	//64 bytes
	FSASizes[3].sizeBlock = 64;
	FSASizes[3].numBlocks = 20;




	for (size_t i = 0; i < 4; i++)
	{

		fixedBlockAllocatorsAvailable[i] = new (i_blockAllocator) FixedBlockAllocator (FSASizes[i].sizeBlock,FSASizes[i].numBlocks, i_blockAllocator);
	}




}
