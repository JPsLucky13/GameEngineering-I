#pragma once
#include "GLib.h"
#include "GameObject.h"
#include "Renderer.h"
namespace Engine {

	class Sprite {

	public:

		Sprite(GameObject* object, const char * i_pFilename);
		~Sprite();

		GLib::Sprites::Sprite * sprite;

	private:
		GameObject * m_pObject;
		Renderer * m_Renderer;
	};



}