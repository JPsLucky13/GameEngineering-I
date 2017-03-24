#pragma once
#include "Collision.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Debug.h"
#include "FloatCheck.h"

namespace Engine
{

	void Collision::CheckCollisions(std::vector<Engine::SmartPointer<Engine::Actor>>& i_actorsToAdd, float i_LastFrameTime)
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
		
			//On Y Axis
			float AProjectionOntoB_Y = fabs(AExtentsXInB.y()) + fabs(AExtentsYInB.y());
			
			//Velocity calculations for A in B
			Engine::Vector3 VelARelToB = Engine::Vector3(i_actorsToAdd[i]->getGObject()->GetVelocity().x() - i_actorsToAdd[j]->getGObject()->GetVelocity().x(), i_actorsToAdd[i]->getGObject()->GetVelocity().y() - i_actorsToAdd[j]->getGObject()->GetVelocity().y(), 0.0f);

			Engine::Vector4 VelAInB = mWorldToB.MultiplyRight(Engine::Vector4(VelARelToB.x(), VelARelToB.y(), VelAInB.z(), 0.0f));

			//The edges of B
			float BLeft = i_actorsToAdd[j]->getBoundingBox().center.x() - (i_actorsToAdd[j]->getBoundingBox().extents.x() + AProjectionOntoB_X);
			float BRight = i_actorsToAdd[j]->getBoundingBox().center.x() + (i_actorsToAdd[j]->getBoundingBox().extents.x() + AProjectionOntoB_X);

			//Top edges of B
			float BBottom = i_actorsToAdd[j]->getBoundingBox().center.y() - (i_actorsToAdd[j]->getBoundingBox().extents.y() + AProjectionOntoB_Y);
			float BTop = i_actorsToAdd[j]->getBoundingBox().center.y() + (i_actorsToAdd[j]->getBoundingBox().extents.y() + AProjectionOntoB_Y);

			float t_CloseAInBX = 0.0f;
			float t_OpenAInBX = 0.0f;

			

			if(!Engine::floatEpsilonEqual(VelAInB.x(),0.0f))
			{ 
				//Times on X axis
				t_CloseAInBX = (i_actorsToAdd[j]->getBoundingBox().center.x() - i_actorsToAdd[j]->getBoundingBox().extents.x()) - (ABBCenterInB.x() + AProjectionOntoB_X) / VelAInB.x();
				t_OpenAInBX = (i_actorsToAdd[j]->getBoundingBox().center.x() - i_actorsToAdd[j]->getBoundingBox().extents.x()) - (ABBCenterInB.x() - AProjectionOntoB_X) / VelAInB.x();

				//Swap the values
				if (t_CloseAInBX > t_OpenAInBX)
				{
					float temp = t_CloseAInBX;
					t_CloseAInBX = t_OpenAInBX;
					t_OpenAInBX = temp;
				}


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
				t_CloseAInBY = (i_actorsToAdd[j]->getBoundingBox().center.y() - i_actorsToAdd[j]->getBoundingBox().extents.y()) - (ABBCenterInB.y() + AProjectionOntoB_Y) / VelAInB.y();
				t_OpenAInBY = (i_actorsToAdd[j]->getBoundingBox().center.y() - i_actorsToAdd[j]->getBoundingBox().extents.y()) - (ABBCenterInB.y() - AProjectionOntoB_Y) / VelAInB.y();

				//Swap the values
				if (t_CloseAInBY > t_OpenAInBY)
				{
					float temp = t_CloseAInBY;
					t_CloseAInBY = t_OpenAInBY;
					t_OpenAInBY = temp;
				}
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

			//The edges of A
			float ALeft = i_actorsToAdd[i]->getBoundingBox().center.x() - (i_actorsToAdd[i]->getBoundingBox().extents.x() + BProjectionOntoA_X);
			float ARight = i_actorsToAdd[i]->getBoundingBox().center.x() + (i_actorsToAdd[i]->getBoundingBox().extents.x() + BProjectionOntoA_X);

			//Top edges of A
			float ABottom = i_actorsToAdd[i]->getBoundingBox().center.y() - (i_actorsToAdd[i]->getBoundingBox().extents.y() + BProjectionOntoA_Y);
			float ATop = i_actorsToAdd[i]->getBoundingBox().center.y() + (i_actorsToAdd[i]->getBoundingBox().extents.y() + BProjectionOntoA_Y);

			float t_CloseBInAX = 0.0f;
			float t_OpenBInAX = 0.0f;

			if (!Engine::floatEpsilonEqual(VelBInA.x(), 0.0f))
			{

				//Times on X axis
				t_CloseBInAX = (i_actorsToAdd[i]->getBoundingBox().center.x() - i_actorsToAdd[i]->getBoundingBox().extents.x()) - (BBBCenterInA.x() + BProjectionOntoA_X) / VelBInA.x();
				t_OpenBInAX = (i_actorsToAdd[i]->getBoundingBox().center.x() - i_actorsToAdd[i]->getBoundingBox().extents.x()) - (BBBCenterInA.x() - BProjectionOntoA_X) / VelBInA.x();

				if (t_CloseBInAX > t_OpenBInAX)
				{
					float temp = t_CloseBInAX;
					t_CloseBInAX = t_OpenBInAX;
					t_OpenBInAX = temp;
				}

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
				t_CloseBInAY = (i_actorsToAdd[i]->getBoundingBox().center.y() - i_actorsToAdd[i]->getBoundingBox().extents.y()) - (BBBCenterInA.y() + BProjectionOntoA_Y) / VelBInA.y();
				t_OpenBInAY = (i_actorsToAdd[i]->getBoundingBox().center.y() - i_actorsToAdd[i]->getBoundingBox().extents.y()) - (BBBCenterInA.y() - BProjectionOntoA_Y) / VelBInA.y();

				if (t_CloseBInAY > t_OpenBInAY)
				{
					float temp = t_CloseBInAY;
					t_CloseBInAY = t_OpenBInAY;
					t_OpenBInAY = temp;
				}
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
			


			//Resolve if there was a collision
			if (!IsSeparated)
			{
				DEBUG_LOG_OUTPUT("There was a collision!");
			}
			
			

			}
		}

	}
}
