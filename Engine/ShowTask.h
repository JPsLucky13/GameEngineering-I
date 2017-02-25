#pragma once
#include <assert.h>
#include <conio.h>
#include <stdio.h>
#include <queue>
#include <Windows.h>
#include "ThreadedFileProcessor.h"
#include "Actor.h"
namespace Engine
{
	class ShowTask : public ThreadedFileProcessor::LoadTask
	{
	public:
		ShowTask(const char * i_pFilename, const char * i_pObjectName, std::vector<Engine::SmartPointer<Engine::Actor>>& i_actorsToAdd, Mutex& i_actorMu);
		virtual void ProcessFileContents(uint8_t * i_pBuffer, uint32_t i_BufferBytes);
	private:
		const char * m_FileName;
		std::vector<Engine::SmartPointer<Engine::Actor>>& m_actors;
		Mutex& m_actorMutex;
	};
	


}

