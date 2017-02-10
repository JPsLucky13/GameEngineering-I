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
			blockAllocator.create(1024 * 1024, 100);
			GetBlockAllocator(&blockAllocator);

			GetFSAManager(&fsaManager);
			fsaManager.CreateFSAs(&blockAllocator);

		}

	void EngineHandler::Run()
	{

	}

		void EngineHandler::Shutdown()
		{
			blockAllocator.destroy();

		}

}