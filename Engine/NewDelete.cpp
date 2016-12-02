#include "NewDelete.h"




//To set a static pointer to the block allocator
Engine::BlockAllocator * GetBlockAllocator(Engine::BlockAllocator * blockAllocator) {
	static Engine::BlockAllocator * blockAllocatorRef = blockAllocator;
	
	return blockAllocatorRef;
}



//void * operator new(size_t i_size)
//{
//	DEBUG_LOG_MESSAGE("Calling new(size_t) with (%zx).\n", i_size);
//
//	return GetBlockAllocator(nullptr)->_alloc(i_size);
//
//}
//
//
//void operator delete(void * ptr)
//{
//
//	DEBUG_LOG_MESSAGE("Calling delete(void *) with (%zx).\n", ptr);
//
//	GetBlockAllocator(nullptr)->_free(ptr);
//}
//
//void * operator new(size_t i_size ,const char * file, const char * func, const unsigned int line)
//{
//	DEBUG_LOG_MESSAGE("Calling new(size_t,const char*,const char*,const unsigned int)\n Size: %zu\n File: %s\n Func: %s\n Line: %d\n ) with (%zx).\n", i_size,file,func,line);
//
//	return GetBlockAllocator(nullptr)->_alloc(i_size);
//
//}
//
//void operator delete(void * ptr, const char * file, const char * func, const unsigned int line)
//{
//	DEBUG_LOG_MESSAGE("Calling delete(size_t,const char*,const char*,const unsigned int)\n Size: %zu\n File: %s\n Func: %s\n Line: %d\n ) with (%zx).\n", ptr, file, func, line);
//
//	GetBlockAllocator(nullptr)->_free(ptr);
//}
//
//void * operator new[](size_t i_size)
//{
//	DEBUG_LOG_MESSAGE("Calling new(size_t) with (%zx).\n", i_size);
//
//	return GetBlockAllocator(nullptr)->_alloc(i_size);
//
//}
//
//void operator delete[](void * ptr)
//{
//
//	DEBUG_LOG_MESSAGE("Calling delete(void *) with (%zx).\n", ptr);
//
//	GetBlockAllocator(nullptr)->_free(ptr);
//
//}
