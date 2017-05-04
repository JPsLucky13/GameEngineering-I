#include "Input.h"
#include <stdio.h>

namespace Engine{

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
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
	if (key == 'A')
	{
		Input::keyHandler.A.m_isDown = bWentDown;
	}
	if (key == 'S')
	{
		Input::keyHandler.S.m_isDown = bWentDown;
	}
	if (key == 'W')
	{
		Input::keyHandler.W.m_isDown = bWentDown;
	}
	if (key == 'D')
	{
		Input::keyHandler.D.m_isDown = bWentDown;
	}

	if (key == 'Q')
	{
		Input::keyHandler.Q.m_isDown = bWentDown;
	}

	if (key == 'Z')
	{
		Input::keyHandler.Z.m_isDown = bWentDown;
	}

}

KeyboardHandler Input::keyHandler;

void Input::Read()
{
	// Set a callback for notification of key presses
	GLib::SetKeyStateChangeCallback(TestKeyCallback);
}

}