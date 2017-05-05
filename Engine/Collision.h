#pragma once
#include "Actor.h"
#include <vector>
namespace Engine
{
		struct CollisionPair
		{
			float m_CollisionTime;
			Vector3 m_CollisionNormal;
			Engine::WeakPointer<Engine::Actor> m_CollisionObjects[2];


		};

	class Collision {


	public:

		static void CheckCollisions(Engine::SmartPointer<Engine::Actor> & i_actorA, Engine::SmartPointer<Engine::Actor> & i_actorB, float i_LastFrameTime);


	};



}