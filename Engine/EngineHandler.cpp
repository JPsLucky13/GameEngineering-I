#include "EngineHandler.h"
#include "NewDelete.h"
#include "Timer.h"
namespace Engine{	




	EngineHandler::EngineHandler()
	{
	}

	EngineHandler::~EngineHandler()
	{
	}

	void EngineHandler::Init()
		{

			//Creating the block allocator
			blockAllocator.create(2048 * 2048, 300);
			GetBlockAllocator(&blockAllocator);

			fsaManager.CreateFSAs(&blockAllocator);
			GetFSAManager(&fsaManager);

		}

	void EngineHandler::Run()
	{

	}

	void EngineHandler::Shutdown()
	{
			blockAllocator.destroy();

	}

}