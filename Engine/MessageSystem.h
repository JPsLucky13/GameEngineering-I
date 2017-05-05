#pragma once
#include "HashedString.h"
#include <functional>
#include <vector>
#include <map>
#include "SmartPointer.h"
#include "Actor.h"
#include "Mutex.h"
#include "Collision.h"

namespace Engine
{

	

	class MessageSystem
	{
	public:
		static MessageSystem * Create();
		static MessageSystem * GetInstance();
		
		void RegisterMessageHandler(const HashedString & i_Message, const std::function<void()> & i_Handler);
		void RegisterMessageHandlerCollision(const HashedString & i_Message, const std::function<void(const Engine::CollisionPair &, const Engine::Vector3 &)> & i_Handler);
		void BroadCast(const HashedString & i_Message);
		void BroadCastCollision(const HashedString & i_Message, const Engine::CollisionPair & i_Pair, const Engine::Vector3 & i_ColNormal);

	private:
		Engine::Mutex messageMu;
		std::map<HashedString, std::vector<std::function<void()>>> messageMap;
		std::map<HashedString, std::vector<std::function<void( const Engine::CollisionPair &, const Engine::Vector3 &)>>> messageMapCollision;

		static MessageSystem * instance;
		MessageSystem();
	};


	


}