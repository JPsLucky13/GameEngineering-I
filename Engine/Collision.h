#pragma once
#include "Actor.h"
#include <vector>
namespace Engine
{

	class Collision {



	public:
		static void CheckCollisions(std::vector<Engine::SmartPointer<Engine::Actor>>& i_actorsToAdd, float i_LastFrameTime);


	};



}