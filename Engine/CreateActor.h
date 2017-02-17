#pragma once
#include "Actor.h"
#include "SmartPointer.h"
#include "lua.hpp"
namespace Engine {

	
	SmartPointer<Actor> CreateActor(const char * i_pFilename);
	size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats);
}