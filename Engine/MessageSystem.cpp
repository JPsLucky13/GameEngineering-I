#include "MessageSystem.h"

Engine::MessageSystem * Engine::MessageSystem::instance = NULL;


Engine::MessageSystem::MessageSystem() :
	messageMu(false, "MessageMutex")
{
	
}

Engine::MessageSystem * Engine::MessageSystem::Create()
{
	if (instance == nullptr)
	{
		instance = new MessageSystem();
		return instance;
	}
	else
	{
		return instance;
	}
}

Engine::MessageSystem * Engine::MessageSystem::GetInstance()
{
	return instance;
}

void Engine::MessageSystem::RegisterMessageHandler(const HashedString & i_Message, std::function<void()> i_Handler)
{

	messageMu.Acquire();

	if (messageMap.count(i_Message) > 0)
	{
		std::vector<std::function<void()>> tempSet = messageMap.at(i_Message);
		tempSet.push_back(i_Handler);
	}

	else
	{
		std::vector<std::function<void()>> tempSet;
		tempSet.push_back(i_Handler);
		messageMap.insert(std::pair<HashedString , std::vector<std::function<void()>>>(i_Message, tempSet));
	}

	messageMu.Release();
}

void Engine::MessageSystem::BroadCast(const HashedString & i_Messager)
{
	const std::vector<std::function<void()>>& function_list = messageMap[i_Messager];
	const size_t num_functions = function_list.size();

	for (size_t i = 0; i < num_functions; ++i)
	{
		function_list[i]();
	}
}
