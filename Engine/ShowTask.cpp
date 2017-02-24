
#include "ShowTask.h"
#include "CreateActor.h"

namespace Engine
{

	ShowTask::ShowTask(const char * i_pFilename, std::vector<Engine::SmartPointer<Engine::Actor>>& i_actorsToAdd):
	ThreadedFileProcessor::LoadTask(i_pFilename),
	m_FileName(i_pFilename),
	m_actors(i_actorsToAdd)
	{}

	void ShowTask::ProcessFileContents(uint8_t * i_pBuffer, uint32_t i_BufferBytes)
	{
		if ((i_pBuffer != NULL) && (i_BufferBytes > 0))
		{
			m_actors.push_back(Engine::CreateActor(m_FileName));
		}
	}

}