#pragma once
#include "Collision.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Debug.h"
#include "FloatCheck.h"
#include "ProfilerUtils.h"
namespace Engine
{

	void Collision::CheckCollisions(std::vector<Engine::SmartPointer<Engine::Actor>>& i_actorsToAdd, float i_LastFrameTime)
	{
		//PROFILE_SCOPE_BEGIN("Engine::Collision::CheckCollisions");


		CollisionPair EarliestCollision;
		EarliestCollision.m_CollisionTime = i_LastFrameTime;

		Engine::Vector3 colNormal;


		for (size_t i = 0; i < i_actorsToAdd.size(); i++)
		{

			for(size_t j=i + 1; j < i_actorsToAdd.size(); j++)
			{ 
				
			//Calculate the earliest collision
			float colTime = 0.0f;


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
		
			//On Y Axis
			float AProjectionOntoB_Y = fabs(AExtentsXInB.y()) + fabs(AExtentsYInB.y());
			
			//Velocity calculations for A in B
			Engine::Vector3 VelARelToB = Engine::Vector3(i_actorsToAdd[i]->getGObject()->GetVelocity().x() - i_actorsToAdd[j]->getGObject()->GetVelocity().x(), i_actorsToAdd[i]->getGObject()->GetVelocity().y() - i_actorsToAdd[j]->getGObject()->GetVelocity().y(), 0.0f);

			Engine::Vector4 VelAInB = mWorldToB.MultiplyRight(Engine::Vector4(VelARelToB.x(), VelARelToB.y(), VelAInB.z(), 0.0f));

			float BextentsX = i_actorsToAdd[j]->getBoundingBox().extents.x() + AProjectionOntoB_X;
			float BextentsY = i_actorsToAdd[j]->getBoundingBox().extents.y() + AProjectionOntoB_Y;

			//The edges of B
			float BLeft = i_actorsToAdd[j]->getBoundingBox().center.x() - BextentsX;
			float BRight = i_actorsToAdd[j]->getBoundingBox().center.x() + BextentsX;

			//Top edges of B
			float BBottom = i_actorsToAdd[j]->getBoundingBox().center.y() - BextentsY;
			float BTop = i_actorsToAdd[j]->getBoundingBox().center.y() + BextentsY;

			float t_CloseAInBX = 0.0f;
			float t_OpenAInBX = 0.0f;

			

			if(!Engine::floatEpsilonEqual(VelAInB.x(),0.0f))
			{ 
				//Times on X axis
				t_CloseAInBX = (BLeft - ABBCenterInB.x())/ VelAInB.x();
				t_OpenAInBX = (BRight - ABBCenterInB.x())/ VelAInB.x();

				//Swap the values
				if (t_CloseAInBX > t_OpenAInBX)
				{
					float temp = t_CloseAInBX;
					t_CloseAInBX = t_OpenAInBX;
					t_OpenAInBX = temp;
				}

				//The axis for the collision
				Engine::Vector4 BxInWorld = mBToWorld.MultiplyLeft(Engine::Vector4(1.0f, 0.0f, 0.0f, 0.0f));

				//The normal to the collision
				colNormal = Engine::Vector3(BxInWorld.x(), BxInWorld.y(),0.0f);
				
				
			}

			else
			{

				if (!IsSeparated)
				{
					if (ABBCenterInB.x() >= BLeft && ABBCenterInB.x() <= BRight)
					{
						IsSeparated = false;
					}
					else
					{
						IsSeparated = true;
					}
				}
				
			}


			float t_CloseAInBY = 0.0f;
			float t_OpenAInBY = 0.0f;

			if (!Engine::floatEpsilonEqual(VelAInB.y(), 0.0f))
			{

				//Times on Y axis
				t_CloseAInBY = (BBottom - ABBCenterInB.y())/ VelAInB.y();
				t_OpenAInBY = (BTop - ABBCenterInB.y())/ VelAInB.y();

				//Swap the values
				if (t_CloseAInBY > t_OpenAInBY)
				{
					float temp = t_CloseAInBY;
					t_CloseAInBY = t_OpenAInBY;
					t_OpenAInBY = temp;
				}

				//The axis for the collision
				Engine::Vector4 ByInWorld = mBToWorld.MultiplyLeft(Engine::Vector4(0.0f, 1.0f, 0.0f, 0.0f));

				//The normal to the collision
				colNormal = Engine::Vector3(ByInWorld.x(), ByInWorld.y(), 0.0f);
				
			}

			else
			{
				if (!IsSeparated)
				{
					if (ABBCenterInB.y() >= BBottom && ABBCenterInB.y() <= BTop)
					{
						IsSeparated = false;
					}
					else
					{
						IsSeparated = true;
					}
				}

			}


			//Rotation Test

			//if(!IsSeparated)
			//IsSeparated = fabs(ABBCenterInB.x() - i_actorsToAdd[j]->getBoundingBox().center.x()) > i_actorsToAdd[j]->getBoundingBox().extents.x() + AProjectionOntoB_X;


			//if (!IsSeparated)
			//IsSeparated = fabs(ABBCenterInB.y() - i_actorsToAdd[j]->getBoundingBox().center.y()) > i_actorsToAdd[j]->getBoundingBox().extents.y() + AProjectionOntoB_Y;

			//Check axis for B in A
			Engine::Vector4 BBBCenterInWorld = mBToWorld.MultiplyRight(Engine::Vector4(i_actorsToAdd[j]->getBoundingBox().center.x(),i_actorsToAdd[j]->getBoundingBox().center.y(), 0.0f, 1.0f));
			Engine::Vector4 BBBCenterInA = mWorldToA.MultiplyRight(Engine::Vector4(BBBCenterInWorld.x(), BBBCenterInWorld.y(), BBBCenterInWorld.z(), 1.0f));

			//Calculate Projection 
			Engine::Vector4 BExtentsXInA = mBToA.MultiplyRight(Engine::Vector4(i_actorsToAdd[j]->getBoundingBox().extents.x(), 0.0f, 0.0f, 0.0f));
			Engine::Vector4 BExtentsYInA = mBToA.MultiplyRight(Engine::Vector4(0.0f, i_actorsToAdd[j]->getBoundingBox().extents.y(), 0.0f, 0.0f));

			//On X Axis
			float BProjectionOntoA_X = fabs(BExtentsXInA.x()) + fabs(BExtentsYInA.x());

			//On Y Axis
			float BProjectionOntoA_Y = fabs(BExtentsXInA.y()) + fabs(BExtentsYInA.y());

			//Velocity calculations for B in A
			Engine::Vector3 VelBRelToA = Engine::Vector3(i_actorsToAdd[j]->getGObject()->GetVelocity().x() - i_actorsToAdd[i]->getGObject()->GetVelocity().x(), i_actorsToAdd[j]->getGObject()->GetVelocity().y() - i_actorsToAdd[i]->getGObject()->GetVelocity().y(), 0.0f);

			Engine::Vector4 VelBInA = mWorldToA.MultiplyRight(Engine::Vector4(VelBRelToA.x(), VelBRelToA.y(), VelBRelToA.z(), 0.0f));

			float AextentsX = i_actorsToAdd[i]->getBoundingBox().extents.x() + BProjectionOntoA_X;
			float AextentsY = i_actorsToAdd[i]->getBoundingBox().extents.y() + BProjectionOntoA_Y;

			//The edges of A
			float ALeft = i_actorsToAdd[i]->getBoundingBox().center.x() - AextentsX;
			float ARight = i_actorsToAdd[i]->getBoundingBox().center.x() + AextentsX;

			//Top edges of A
			float ABottom = i_actorsToAdd[i]->getBoundingBox().center.y() - AextentsY;
			float ATop = i_actorsToAdd[i]->getBoundingBox().center.y() + AextentsY;

			float t_CloseBInAX = 0.0f;
			float t_OpenBInAX = 0.0f;

			if (!Engine::floatEpsilonEqual(VelBInA.x(), 0.0f))
			{

				//Times on X axis
				t_CloseBInAX = (ALeft - BBBCenterInA.x()) / VelBInA.x();
				t_OpenBInAX = (ARight - BBBCenterInA.x()) / VelBInA.x();

				if (t_CloseBInAX > t_OpenBInAX)
				{
					float temp = t_CloseBInAX;
					t_CloseBInAX = t_OpenBInAX;
					t_OpenBInAX = temp;
				}

				//The axis for the collision
				Engine::Vector4 AxInWorld = mAToWorld.MultiplyLeft(Engine::Vector4(1.0f, 0.0f, 0.0f, 0.0f));

				//The normal to the collision
				colNormal = Engine::Vector3(AxInWorld.x(), AxInWorld.y(), 0.0f);
				

			}

			else
			{
				if (!IsSeparated)
				{
					if (BBBCenterInA.x() >= ALeft && BBBCenterInA.x() <= ARight)
					{
						IsSeparated = false;
					}
					else
					{
						IsSeparated = true;
					}
				}
			}

			float t_CloseBInAY = 0.0f;
			float t_OpenBInAY = 0.0f;

			if (!Engine::floatEpsilonEqual(VelBInA.y(), 0.0f))
			{

				//Times on Y axis
				t_CloseBInAY = (ABottom - BBBCenterInA.y()) / VelBInA.y();
				t_OpenBInAY = (ATop - BBBCenterInA.y())/ VelBInA.y();

				if (t_CloseBInAY > t_OpenBInAY)
				{
					float temp = t_CloseBInAY;
					t_CloseBInAY = t_OpenBInAY;
					t_OpenBInAY = temp;
				}

				//The axis for the collision
				Engine::Vector4 AyInWorld = mAToWorld.MultiplyLeft(Engine::Vector4(0.0f, 1.0f, 0.0f, 0.0f));

				//The normal to the collision
				colNormal = Engine::Vector3(AyInWorld.x(), AyInWorld.y(), 0.0f);
				
			}

			else 
			{
				if (!IsSeparated)
				{
					if (BBBCenterInA.y() >= ABottom && BBBCenterInA.y() <= ATop)
					{
						IsSeparated = false;
					}
					else
					{
						IsSeparated = true;
					}
				}
			
			
			}


			//Retrieve the min open and max close
			float maxClose = 0.0f;
			float minOpen = 0.0f;

			const int sizeCloseTimes = 4;
			const int sizeOpenTimes = 4;

			float closeTimes[sizeCloseTimes] = {t_CloseAInBX,t_CloseAInBY,t_CloseBInAX, t_CloseBInAY };
			float openTimes[sizeOpenTimes] = { t_OpenAInBX,t_OpenAInBY,t_OpenBInAX, t_OpenBInAY };

			for (size_t n = 0; n < sizeCloseTimes - 1; n++)
			{
				if (closeTimes[n] > closeTimes[n + 1])
				{
					maxClose = closeTimes[n];
				}
				else 
				{
					maxClose = closeTimes[n + 1];
				}
			}

			for (size_t m = 0; m < sizeOpenTimes - 1; m++)
			{
				if (openTimes[m] < openTimes[m + 1])
				{
					minOpen = openTimes[m];
				}
				else
				{
					minOpen = openTimes[m + 1];
				}
			}



			
			if (!IsSeparated)
			{
				if (maxClose > i_LastFrameTime || minOpen < 0.0f)
				{
					IsSeparated = true;
				}
				else
				{
					if (maxClose > minOpen)
						IsSeparated = true;
					else
						IsSeparated = false;
				}
			}


			//Rotation Test

			//if (!IsSeparated)
			//IsSeparated = fabs(BBBCenterInA.x() - i_actorsToAdd[i]->getBoundingBox().center.x()) > i_actorsToAdd[i]->getBoundingBox().extents.x() + BProjectionOntoA_X;

			//if (!IsSeparated)
			//IsSeparated = fabs(BBBCenterInA.y() - i_actorsToAdd[i]->getBoundingBox().center.y()) > i_actorsToAdd[i]->getBoundingBox().extents.y() + BProjectionOntoA_Y;
			


				
			colTime = maxClose;

				//Resolve if there was a collision
				if (!IsSeparated)
				{
					
					if (colTime < EarliestCollision.m_CollisionTime)
					{
						EarliestCollision.m_CollisionTime = colTime;
						EarliestCollision.m_CollisionNormal = colNormal;
						EarliestCollision.m_CollisionObjects[0] = i_actorsToAdd[i];
						EarliestCollision.m_CollisionObjects[1] = i_actorsToAdd[j];

						//	Call the collision resolution
						ResolveCollision(EarliestCollision, colNormal);

					}
					//DEBUG_LOG_OUTPUT("There was a collision!");
				}
			}
		}

		//PROFILE_SCOPE_END();

	}
	void Collision::ResolveCollision(CollisionPair & i_Pair, Engine::Vector3 & i_colNormal)
	{

		//Objects A and B
		Engine::Vector2D velA = i_Pair.m_CollisionObjects[0].Acquire()->getGObject()->GetVelocity();
		Engine::Vector2D velB = i_Pair.m_CollisionObjects[1].Acquire()->getGObject()->GetVelocity();

		//The masses of the objects
		float massA = i_Pair.m_CollisionObjects[0].Acquire()->getPhysics().Acquire()->getMass();
		float massB = i_Pair.m_CollisionObjects[1].Acquire()->getPhysics().Acquire()->getMass();

		//Post collision velocities
		Engine::Vector2D velAPost = velA * ((massA - massB) / (massA + massB)) + velB * ((2.0f * massB) / (massA + massB));
		Engine::Vector2D velBPost = velB * ((massB - massA) / (massA + massB)) + velA * ((2.0f * massA) / (massA + massB));

		Engine::Vector2D colNormal = Engine::Vector2D(i_colNormal.x(), i_colNormal.y());
		
		if(!Engine::floatEpsilonEqual(i_colNormal.x(),0.0f) || !Engine::floatEpsilonEqual(i_colNormal.y(), 0.0f))
		colNormal.normalize();

		//Post collision velocities with normal
		Engine::Vector2D velAPost2 = velA - (colNormal * Engine::dot(velA,colNormal) * 2.0f);
		Engine::Vector2D velBPost2 = velB - (colNormal * Engine::dot(velB,colNormal) * 2.0f);

		Engine::Vector2D resVelA = velAPost + velAPost2;
		Engine::Vector2D resVelB = velBPost + velBPost2;

		////Cap the velocities
		float maxVelocity = 300.0f;

		if (resVelA.x() >= maxVelocity)
			resVelA.x(maxVelocity);
		if(resVelA.x() <= -maxVelocity)
			resVelA.x(-maxVelocity);

		if (resVelA.y() >= maxVelocity)
			resVelA.y(maxVelocity);
		if(resVelA.y() <= -maxVelocity)
			resVelA.y(-maxVelocity);

		if (resVelB.x() >= maxVelocity)
			resVelB.x(maxVelocity);
		if (resVelB.x() <= -maxVelocity)
			resVelB.x(-maxVelocity);

		if (resVelB.y() >= maxVelocity)
			resVelB.y(maxVelocity);
		if (resVelB.y() <= -maxVelocity)
			resVelB.y(-maxVelocity);

		//Set new velocity
		if (i_Pair.m_CollisionObjects[0].Acquire()->getType() != "Level")
		{
			i_Pair.m_CollisionObjects[0].Acquire()->getGObject()->SetVelocity(resVelA);
		}
		
		if (i_Pair.m_CollisionObjects[1].Acquire()->getType() != "Level")
		{
			i_Pair.m_CollisionObjects[1].Acquire()->getGObject()->SetVelocity(resVelB);
		}


	}
}
