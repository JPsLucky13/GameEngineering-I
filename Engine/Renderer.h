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

	//The Graphics functions
	void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);

	
	};
}