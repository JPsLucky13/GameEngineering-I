#pragma once
#include "KeyboardHandler.h"
#include "GLib.h"

namespace Engine {


		//Test the Key Callback
		void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown);
		//Read the keyboard input
		void Read();

		KeyboardHandler * keyHandler;




	


}