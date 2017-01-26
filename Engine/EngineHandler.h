#pragma once
#include "FSAManager.h"
#include "BlockAllocator.h"
#include "KeyboardHandler.h"
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


	private:
		
		//The block allocator
		BlockAllocator blockAllocator;

		//The memory manager that handles FSA
		FSAManager fsaManager;
	};
}

