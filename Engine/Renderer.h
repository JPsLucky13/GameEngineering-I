#pragma once

#include "GLib.h"


namespace Engine
{
	class Renderer
	{

	public:

	Renderer();
	~Renderer();

	bool Initialize(HINSTANCE i_hInstance, int i_nCmdShow);

	void RunRenderer();

	void ShutdownRenderer();

	void ServiceRenderer(bool bQuit);

	void StartRenderer();

	void StartRenderSprites();

	
	GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);

	
	};
}