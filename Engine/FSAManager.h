#pragma once
#include "FixedBlockAllocator.h"
#include "BlockAllocator.h"

#define _NUM_FSAS 4



namespace Engine{

class FSAManager {

public:

	struct FSAInitData
	{
		size_t sizeBlock;
		size_t numBlocks;
	};


	//Constructor
	FSAManager();

	//Destructor
	~FSAManager();


	//get for the amount of FSAs
	size_t GetNumFSAs() { return numFSAs; }


	//Create the 
	void CreateFSAs(BlockAllocator * i_blockAllocator);


	FixedBlockAllocator * fixedBlockAllocatorsAvailable[_NUM_FSAS];

	FSAInitData FSASizes[_NUM_FSAS];

private:

	size_t numFSAs = _NUM_FSAS;



};


}