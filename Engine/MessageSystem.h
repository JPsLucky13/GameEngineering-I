#pragma once
#include "HashedString.h"
#include <functional>
#include <vector>
#include <map>
#include "SmartPointer.h"
#include "Actor.h"
#include "Mutex.h"

namespace Engine
{

	

	class MessageSystem
	{
	public:
		static MessageSystem * Create();
		static MessageSystem * GetInstance();
		
		void RegisterMessageHandler(const HashedString & i_Message, std::function<void()> i_Handler);
		void BroadCast(const HashedString & i_Message);

	private:
		Engine::Mutex messageMu;
		std::map<HashedString, std::vector<std::function<void()>>> messageMap;

		static MessageSystem * instance;
		MessageSystem();
	};


	


}