#pragma once
#include "FSAManager.h"
#include "BlockAllocator.h"
namespace Engine{

	class EngineHandler {

	public:

		EngineHandler();
		~EngineHandler();

		//Initialize engine
		void Init();

		//Run the engine
		void Run();

		//Shutdown the engine
		void Shutdown();

		
		//The block allocator
		BlockAllocator blockAllocator;

	private:

		//The memory manager that handles FSA
		FSAManager fsaManager;
	};
}

