#include "HashedString.h"
#include <assert.h>
#include <string.h>
#include <stdint.h>

unsigned int Engine::HashedString::Hash(const char * i_string)
{
	assert(i_string);

	return Hash(reinterpret_cast<void*>(const_cast<char*>(i_string)), strlen(i_string));
}

unsigned int Engine::HashedString::Hash(const void * i_bytes, size_t i_byteCount)
{
	const uint8_t * p = static_cast<const uint8_t *>(i_bytes);
	unsigned int hash = 2166136261;

	for (unsigned int i = 0; i < i_byteCount; i++)
		hash = 16777619 * (hash ^ p[i]);

	return hash ^ (hash >> 16);
}
