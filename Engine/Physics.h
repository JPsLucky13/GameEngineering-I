#pragma once
#include "PhysicsInfo.h"
#include "SmartPointer.h"
#include <vector>

namespace Engine {


	class Physics {

	public:
		static Physics * Create();
		~Physics();
		SmartPointer<PhysicsInfo> CreatePhysics(SmartPointer<GameObject>& gameobject,float mass, float drag);
		static Physics * GetInstance();

	private:
		std::vector<SmartPointer<PhysicsInfo>> physicsElements;
		static Physics * instance;
		Physics();

	};

}