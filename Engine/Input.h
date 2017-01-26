#pragma once
#include "KeyboardHandler.h"
#include "GLib.h"

namespace Engine {

	//Test the Key Callback
	void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown);

	class Input
	{


	public:
		static KeyboardHandler keyHandler;
		//Read the keyboard input
		static void Read();

	private:
		Input();
		~Input();
	};



	


}