#pragma once
#include "GLib.h"
#include "GameObject.h"
#include "WeakPointer.h"
namespace Engine {

	class Sprite {

	public:

		Sprite(const WeakPointer<GameObject>& object, const char * i_pFilename);
		~Sprite();
		GLib::Sprites::Sprite * sprite;

	private:
		WeakPointer<GameObject> m_pObject;
		GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
	};



}