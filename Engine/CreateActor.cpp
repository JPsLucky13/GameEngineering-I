#pragma once
#include "CreateActor.h"
#include "FileHandler.h"
#include "Renderer.h"
#include "Physics.h"
#include <string.h>
namespace Engine {


	SmartPointer<Actor> CreateActor(const char * i_pFilename)
	{
		//Start the lua state
		lua_State * pLuaState = luaL_newstate();
		assert(pLuaState);

		//open the library
		luaL_openlibs(pLuaState);


		//The destination of the file
		const char * file = i_pFilename;
		const size_t dest_size = 50;
		char destination[dest_size];
		const char * directory = "..//data/";
		const char * fileType = ".lua";
		
		strncpy_s(destination, dest_size, directory, strlen(directory));
		strcat_s(destination, dest_size, file);
		strcat_s(destination, dest_size, fileType);

		//the parameters for the file to read 
		size_t sizeFile = 0;
		uint8_t * pFileContents = Engine::LoadFile(destination, sizeFile);

		
		
		if (pFileContents && sizeFile)
		{
			int result = 0;
			//Necessary stuff to process our data
			result = luaL_loadbuffer(pLuaState, reinterpret_cast<char *> (pFileContents), sizeFile, nullptr);
			assert(result == 0);

			result = lua_pcall(pLuaState, 0, 0, 0);
			assert(result == 0);

	
			//Find the global table 
			result = lua_getglobal(pLuaState, i_pFilename);
			assert(result == LUA_TTABLE);

			int	type = LUA_TNIL;

			// read the name of the psrite file from lua
			lua_pushstring(pLuaState, "name");

			//get the associated key
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TSTRING);
			const char * pName = lua_tostring(pLuaState, -1);

			char name[dest_size];
			strncpy_s(name, dest_size, pName, strlen(pName));


			//Done with the name
			lua_pop(pLuaState, 1);

			//Read the initial position of the actor
			lua_pushstring(pLuaState, "initial_position");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TTABLE);

			float Position[2] = {1.0f};

			ReadFloatArray(pLuaState, -1, Position, 2);
		
			//Done with the initial position
			lua_pop(pLuaState, 1);
		
			//Read the initial rotation of the actor
			lua_pushstring(pLuaState, "initial_rotation");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TTABLE);

			float Rotation[3] = { 0.0f };

			ReadFloatArray(pLuaState, -1, Rotation, 3);

			//Done with the initial position
			lua_pop(pLuaState, 1);

			//Push the key for the field we want on the stack
			lua_pushstring(pLuaState, "physics_settings");

			type = lua_gettable(pLuaState, -2);
			// It either needs to be a table or not there (no physics applied)
			assert((type == LUA_TNIL) || (type == LUA_TTABLE));


			//Push the key for the field we want on the stack
			lua_pushstring(pLuaState, "mass");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TNUMBER);


			float mass = float(lua_tonumber(pLuaState, -1));

			//Push the key for the field we want on the stack
			lua_pushstring(pLuaState, "drag");
			type = lua_gettable(pLuaState, -3);
			assert(type == LUA_TNUMBER);

			float drag = float (lua_tonumber(pLuaState, -1));

			lua_pop(pLuaState,3);

			//Pop the player1 table
			lua_pop(pLuaState,1);

			int stack_items = lua_gettop(pLuaState);
			assert(stack_items == 0);

			delete[] pFileContents;
			lua_close(pLuaState);

			//Create the smart pointer with game object
			Engine::SmartPointer<Engine::GameObject> gameObject(new Engine::GameObject());
			gameObject->SetPosition(Engine::Vector2D(Position[0], Position[1]));
			gameObject->SetRotation(Engine::Vector3(Rotation[0], Rotation[1], Rotation[2]));

			//Create the physics info
			Engine::WeakPointer<Engine::PhysicsInfo> physicsWeakp(Engine::Physics::GetInstance()->CreatePhysics(gameObject,mass, drag));

			//The destination of the file
			const size_t dest_size = 50;
			char destination[dest_size];
			const char * directory = "data\\";
			const char * fileType = ".dds";

			strncpy_s(destination, dest_size, directory, strlen(directory));
			strcat_s(destination, dest_size, name);
			strcat_s(destination, dest_size, fileType);


			//Create the sprite info
			Engine::WeakPointer<Engine::Sprite> spriteWeakp(Engine::Renderer::GetInstance()->CreateSpriteIcon(gameObject, destination));

			Actor * new_Actor = new Actor(name,gameObject, physicsWeakp, spriteWeakp);

			//Creating AABB
			Engine::Vector2D center = Engine::Vector2D(0.0f, spriteWeakp.Acquire()->getHeight() / 2.0f);
			Engine::Vector2D extents = Engine::Vector2D(spriteWeakp.Acquire()->getWidth() / 2.0f, spriteWeakp.Acquire()->getHeight() / 2.0f);
			
			new_Actor->setBoundingBox(center, extents);
			Engine::SmartPointer<Engine::Actor> actorObject(new_Actor);

			return actorObject;
		}

		return nullptr;
	}

	size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats)
	{
		assert(i_pState);
		assert(lua_gettop(i_pState) >= -i_index);
		assert(lua_type(i_pState, i_index) == LUA_TTABLE);
		size_t				index = 0;
		lua_pushnil(i_pState);
		while (lua_next(i_pState, i_index - 1) != 0)
		{
			if (lua_type(i_pState, -1) == LUA_TNUMBER)
			{
				o_pFloats[index] = float(lua_tonumber(i_pState, -1));
			}
			else
			{
				// DEBUG_PRINT( "Expected a number at position %d while reading table as float array.\n", index );
			}
			// pop the value now that we've retrieved it
			lua_pop(i_pState, 1);
			if (++index == i_numFloats)
			{
				lua_pop(i_pState, 1);
				break;
			}
		}
		return index;
	}

}