#include "Input.h"
#include <stdio.h>

void Engine::TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

void Engine::Read()
{
	// Set a callback for notification of key presses
	GLib::SetKeyStateChangeCallback(TestKeyCallback);
}
