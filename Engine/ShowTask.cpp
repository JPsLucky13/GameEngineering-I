
#include "ShowTask.h"
#include "CreateActor.h"
#include "MessageSystem.h"

namespace Engine
{

	ShowTask::ShowTask(const char * i_pFilename, const char * i_pObjectName,std::vector<Engine::SmartPointer<Engine::Actor>>& i_actorsToAdd, Mutex& i_actorMu):
	ThreadedFileProcessor::LoadTask(i_pFilename),
	m_FileName(i_pObjectName),
	m_actors(i_actorsToAdd),
	m_actorMutex(i_actorMu)
	{}

	void ShowTask::ProcessFileContents(uint8_t * i_pBuffer, uint32_t i_BufferBytes)
	{
		m_actorMutex.Acquire();

		if ((i_pBuffer != NULL) && (i_BufferBytes > 0))
		{
			m_actors.push_back(Engine::CreateActor(m_FileName));
		}

		m_actorMutex.Release();

		//Call broadcast that actor was created
		Engine::MessageSystem::GetInstance()->BroadCast("ActorCreated");


	}





}