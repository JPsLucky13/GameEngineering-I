#pragma once
#include "Collision.h"
#include "Matrix4x4.h"
#include "Debug.h"

namespace Engine
{

	void Collision::CheckCollisions(std::vector<Engine::SmartPointer<Engine::Actor>>& i_actorsToAdd)
	{
		for (size_t i = 0; i < i_actorsToAdd.size(); i++)
		{

			for(size_t j=i + 1; j < i_actorsToAdd.size(); j++)
			{ 
		
			//Separation check
			bool IsSeparated = false;
				
			//Store temporary matrices for object A
			Engine::Matrix4x4 mRotA = Engine::Matrix4x4::CreateZRotation(i_actorsToAdd[i]->getGObject()->GetRotation().z());
			Engine::Matrix4x4 mTransA = Engine::Matrix4x4::CreateTranslation(Engine::Vector4(i_actorsToAdd[i]->getGObject()->GetPosition().x(), i_actorsToAdd[i]->getGObject()->GetPosition().y(), 0.0f, 0.0f));
		
			Engine::Matrix4x4 mAToWorld = mTransA * mRotA;
			//The inverse matrix
			Engine::Matrix4x4 mWorldToA = mAToWorld.GetInverse();

		
			//Store temporary matrices for object B
			Engine::Matrix4x4 mRotB = Engine::Matrix4x4::CreateZRotation(i_actorsToAdd[j]->getGObject()->GetRotation().z());
			Engine::Matrix4x4 mTransB = Engine::Matrix4x4::CreateTranslation(Engine::Vector4(i_actorsToAdd[j]->getGObject()->GetPosition().x(), i_actorsToAdd[j]->getGObject()->GetPosition().y(), 0.0f, 0.0f));

			Engine::Matrix4x4 mBToWorld = mTransB * mRotB;
			//The inverse matrix
			Engine::Matrix4x4 mWorldToB = mBToWorld.GetInverse();

			//Conversion matrices
			Engine::Matrix4x4 mAToB = mWorldToB * mAToWorld;
			Engine::Matrix4x4 mBToA = mWorldToA * mBToWorld;


			//Check axis for A in B
			Engine::Vector4 ABBCenterInWorld = mAToWorld.MultiplyRight(Engine::Vector4(i_actorsToAdd[i]->getBoundingBox().center.x(),i_actorsToAdd[i]->getBoundingBox().center.y(),0.0f,1.0f));
			Engine::Vector4 ABBCenterInB = mWorldToB.MultiplyRight(Engine::Vector4(ABBCenterInWorld.x(), ABBCenterInWorld.y(), ABBCenterInWorld.z(), 1.0f));

			//Calculate Projection 
			Engine::Vector4 AExtentsXInB = mAToB.MultiplyRight(Engine::Vector4(i_actorsToAdd[i]->getBoundingBox().extents.x(), 0.0f,0.0f,0.0f));
			Engine::Vector4 AExtentsYInB = mAToB.MultiplyRight(Engine::Vector4(0.0f,i_actorsToAdd[i]->getBoundingBox().extents.y(),0.0f, 0.0f));
			
			

			//On X Axis
			float AProjectionOntoB_X = fabs(AExtentsXInB.x()) + fabs(AExtentsYInB.x());
		
			
			if(!IsSeparated)
			IsSeparated = fabs(ABBCenterInB.x() - i_actorsToAdd[j]->getBoundingBox().center.x()) > i_actorsToAdd[j]->getBoundingBox().extents.x() + AProjectionOntoB_X;

			//On Y Axis
			float AProjectionOntoB_Y = fabs(AExtentsXInB.y()) + fabs(AExtentsYInB.y());

			if (!IsSeparated)
			IsSeparated = fabs(ABBCenterInB.y() - i_actorsToAdd[j]->getBoundingBox().center.y()) > i_actorsToAdd[j]->getBoundingBox().extents.y() + AProjectionOntoB_Y;

			//Check axis for B in A
			Engine::Vector4 BBBCenterInWorld = mBToWorld.MultiplyRight(Engine::Vector4(i_actorsToAdd[j]->getBoundingBox().center.x(),i_actorsToAdd[j]->getBoundingBox().center.y(), 0.0f, 1.0f));
			Engine::Vector4 BBBCenterInA = mWorldToA.MultiplyRight(Engine::Vector4(BBBCenterInWorld.x(), BBBCenterInWorld.y(), BBBCenterInWorld.z(), 1.0f));

			//Calculate Projection 
			Engine::Vector4 BExtentsXInA = mBToA.MultiplyRight(Engine::Vector4(i_actorsToAdd[j]->getBoundingBox().extents.x(), 0.0f, 0.0f, 0.0f));
			Engine::Vector4 BExtentsYInA = mBToA.MultiplyRight(Engine::Vector4(0.0f, i_actorsToAdd[j]->getBoundingBox().extents.y(), 0.0f, 0.0f));

			//On X Axis
			float BProjectionOntoA_X = fabs(BExtentsXInA.x()) + fabs(BExtentsYInA.x());

			if (!IsSeparated)
			IsSeparated = fabs(BBBCenterInA.x() - i_actorsToAdd[i]->getBoundingBox().center.x()) > i_actorsToAdd[i]->getBoundingBox().extents.x() + BProjectionOntoA_X;



			//On Y Axis
			float BProjectionOntoA_Y = fabs(BExtentsXInA.y()) + fabs(BExtentsYInA.y());

			if (!IsSeparated)
			IsSeparated = fabs(BBBCenterInA.y() - i_actorsToAdd[i]->getBoundingBox().center.y()) > i_actorsToAdd[i]->getBoundingBox().extents.y() + BProjectionOntoA_Y;
			
			
			//Resolve if there was a collision
			if (!IsSeparated)
			{
				DEBUG_LOG_OUTPUT("There was a collision!");
			}

			

			}
		}

	}
}
