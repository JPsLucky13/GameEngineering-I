
#include "Physics.h"
namespace Engine {

	Physics * Physics::instance = NULL;


	Physics::Physics()
	{}
	
	Physics::~Physics()
	{
	}

	Physics * Physics::Create()
	{
		if (instance == nullptr)
		{
			instance = new Physics();
			return instance;
		}
		else
		{
			return instance;
		}
	}


	SmartPointer<PhysicsInfo> Physics::CreatePhysics(SmartPointer<GameObject>& gameObject,float mass, float drag)
	{
		SmartPointer<PhysicsInfo> pInfo(new PhysicsInfo(gameObject,mass, drag));
		physicsElements.push_back(pInfo);
		return pInfo;
	}

	Physics * Physics::GetInstance()
	{
		return instance;
	}

}