#pragma once

#include "GLib.h"
#include "Sprite.h"
#include "SmartPointer.h"
#include <vector>

namespace Engine
{
	
	class Renderer {
	
	public:

		static Renderer * Create();

		bool Initialize(HINSTANCE i_hInstance, int i_nCmdShow);

		void RunRenderer();

		void ShutdownRenderer();

		void ServiceRenderer(bool bQuit);

		void StartRenderer();

		void StartRenderSprites();
	
		SmartPointer<Sprite> CreateSpriteIcon(SmartPointer<GameObject>& gameObject ,const  char * i_pFileName);

		static Renderer * GetInstance();


		~Renderer();
	
	private:
		std::vector<SmartPointer<Sprite>> smartSprites;
		static Renderer * instance;
		Renderer();

	};
}