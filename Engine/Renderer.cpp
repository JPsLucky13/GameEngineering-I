#pragma once
#include <assert.h> 
#include <stdio.h>
#include "Renderer.h"
#include "FileHandler.h"

namespace Engine {
	
		Renderer * Renderer::instance = nullptr;

		Renderer::Renderer()
		{
		}

		SmartPointer<Sprite>  Renderer::CreateSpriteIcon(SmartPointer<GameObject> &gameObject, const char * i_pFileName)
		{
			SmartPointer<Sprite> sprite(new Sprite(gameObject, i_pFileName));

			smartSprites.push_back(sprite);
			return sprite;
		}

		Renderer * Renderer::GetInstance()
		{
			return instance;
		}

		Renderer::~Renderer()
		{
		}


		Renderer *  Renderer::Create()
		{
			if (instance == nullptr)
			{
				instance = new Renderer();
				return instance;
			}
			else
			{
				return instance;
			}
		}
		//Initializes the Graphics library
		bool  Renderer::Initialize(HINSTANCE i_hInstance, int i_nCmdShow)
		{

			if (GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600))
				return true;
			else
				return false;
		}

		void  Renderer::ServiceRenderer(bool bQuit)
		{
			// We need to let GLib do it's thing. 
			GLib::Service(bQuit);
		}

		void  Renderer::StartRenderer()
		{
			// Tell GLib that we want to start rendering
			GLib::BeginRendering();
		}

		void Renderer::StartRenderSprites()
		{
			// Tell GLib that we want to render some sprites
			GLib::Sprites::BeginRendering();
		}


	

}

