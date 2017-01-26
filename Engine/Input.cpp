#include "Input.h"
#include <stdio.h>


void  Engine::TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey %d went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG

	//set booleans for the keys
	char key = static_cast<char>(i_VKeyID);


	//Check if keys are down
	if (key == 'A' && bWentDown)
	{
		Engine::keyHandler->A.m_isDown = true;
	}
	if (key == 'S' && bWentDown)
	{
		Engine::keyHandler->S.m_isDown = true;
	}
	if (key == 'W' && bWentDown)
	{
		Engine::keyHandler->W.m_isDown = true;
	}
	if (key == 'D' && bWentDown)
	{
		Engine::keyHandler->D.m_isDown = true;
	}



	//Check if keys are down
	if (key == 'A' && !bWentDown)
	{
		Engine::keyHandler->A.m_isDown = false;
	}
	if (key == 'S' && !bWentDown)
	{
		Engine::keyHandler->S.m_isDown = false;
	}
	if (key == 'W' && !bWentDown)
	{
		Engine::keyHandler->W.m_isDown = false;
	}
	if (key == 'D' && !bWentDown)
	{
		Engine::keyHandler->D.m_isDown = false;
	}




}




void Engine::Read()
{
	// Set a callback for notification of key presses
	GLib::SetKeyStateChangeCallback(TestKeyCallback);
}
