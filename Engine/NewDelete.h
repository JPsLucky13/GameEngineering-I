#pragma once
#include "BlockAllocator.h"
#include "FixedBlockAllocator.h"
#include "FSAManager.h"

#ifdef _DEBUG
#define DEBUG_LOG_MESSAGE(fmt,...) Engine::PrintDebugMessage(__FILE__,__FUNCTION__,__LINE__,fmt,__VA_ARGS__)
#define ASSERT(cond,message) assert((cond))

#else
#define DEBUG_LOG_MESSAGE(fmt,...) void(0)
#define ASSERT_MONSTER_NUMBER(cond,message) void (0)
#define ASSERT(cond,message) void(0)

#endif

Engine::BlockAllocator * GetBlockAllocator(Engine::BlockAllocator * blockAllocator);
Engine::FSAManager * GetFSAManager(Engine::FSAManager * i_fsaManager);
Engine::FixedBlockAllocator * FindFixedSizeAllocator(size_t i_size);
void * operator new(size_t i_size);
void operator delete(void * ptr);
void * operator new(size_t i_size, Engine::BlockAllocator * i_BlockAllocator);
void operator delete(void * ptr, Engine::BlockAllocator * i_BlockAllocator);
void * operator new(size_t i_size, const char * file, const char * func, const unsigned int line);
void operator delete(void * ptr, const char * file, const char * func, const unsigned int line);
void * operator new[](size_t i_size);
void operator delete[](void * ptr);
