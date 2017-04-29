#pragma once
#include "Actor.h"
#include <vector>
namespace Engine
{

	class Collision {

		struct CollisionPair
		{
			float m_CollisionTime;
			Vector3 m_CollisionNormal;
			Engine::WeakPointer<Engine::Actor> m_CollisionObjects[2];


		};

	public:

		static void CheckCollisions(std::vector<Engine::SmartPointer<Engine::Actor>>& i_actorsToAdd, float i_LastFrameTime);
		static void ResolveCollision(CollisionPair & i_Pair, Engine::Vector3 & i_colNormal);


	};



}