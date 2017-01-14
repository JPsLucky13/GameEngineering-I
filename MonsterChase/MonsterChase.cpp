// MonsterChase.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <assert.h> 
#include <ctime> //For calling a seed of random numbers
#include "Monster.h"
#include "Player.h"
#include "Debug.h"
#include "GameManager.h"
#include "BlockAllocator.h"
#include "NewDelete.h"
#include "FSAManager.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "GLib.h"


#ifdef _DEBUG
#define TRACK_NEW (__FILE__,__FUNCTION__,__LINE__)
#else
#define TRACK_NEW
#endif


//Monster Chase Unit Test
extern void MonsterChase_UnitTest();

//Float Chek unit test
extern void FloatChecker_UnitTest();


//Block allocator unit test
extern bool HeapManager_UnitTest();

//FSA Unite test
extern void FSA_UnitTest(Engine::FSAManager * i_fsaManager);


//The reverse string in place function
extern char* ReverseString(char * string);

//The bit array unit test
extern void BitArray_UnitTest(void);


extern size_t StringLength(const char * string);


//The Graphics functions


void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	//For blockAllocator Testing

	//The block allocator
	Engine::BlockAllocator blockAllocator;

	//Creating the block allocator
	blockAllocator.create(1024 * 1024, 100);
	GetBlockAllocator(&blockAllocator);

	//The memory manager that handles FSA
	Engine::FSAManager fsaManager;
	GetFSAManager(&fsaManager);
	fsaManager.CreateFSAs(&blockAllocator);






	// first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);

	if (bSuccess)
	{
		// Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		// Create a couple of sprites using our own helper routine CreateSprite
		GLib::Sprites::Sprite * pGoodGuy = CreateSprite("data\\Zero.dds");
		GLib::Sprites::Sprite * pBadGuy = CreateSprite("data\\Vile.dds");

		bool bQuit = false;

		do
		{
			// We need to let GLib do it's thing. 
			GLib::Service(bQuit);

			if (!bQuit)
			{
				// Tell GLib that we want to start rendering
				GLib::BeginRendering();
				// Tell GLib that we want to render some sprites
				GLib::Sprites::BeginRendering();

				if (pGoodGuy)
				{
					static float			moveDist = .01f;
					static float			moveDir = moveDist;

					static GLib::Point2D	Offset = { -180.0f, -100.0f };

					if (Offset.x < -220.0f)
						moveDir = moveDist;
					else if (Offset.x > -140.0f)
						moveDir = -moveDist;

					Offset.x += moveDir;

					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*pGoodGuy, Offset, 0.0f);
				}
				if (pBadGuy)
				{
					static float			moveDist = .02f;
					static float			moveDir = -moveDist;

					static GLib::Point2D	Offset = { 180.0f, -100.0f };

					if (Offset.x > 200.0f)
						moveDir = -moveDist;
					else if (Offset.x < 160.0f)
						moveDir = moveDist;

					Offset.x += moveDir;

					// Tell GLib to render this sprite at our calculated location
					GLib::Sprites::RenderSprite(*pBadGuy, Offset, 0.0f);
				}

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// Tell GLib we're done rendering
				GLib::EndRendering();
			}
		} while (bQuit == false);

		if (pGoodGuy)
			GLib::Sprites::Release(pGoodGuy);
		if (pBadGuy)
			GLib::Sprites::Release(pBadGuy);
		GLib::Shutdown();

		blockAllocator.destroy();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}

GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return NULL;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f },{ 1.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
	if (pSprite == nullptr)
	{
		GLib::Release(pTexture);
		return nullptr;
	}

	// Bind the texture to sprite
	GLib::Sprites::SetTexture(*pSprite, *pTexture);

	return pSprite;
}

void * LoadFile(const char * i_pFilename, size_t & o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE * pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t * pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}







/*
int main(){
	//MonsterChase_UnitTest();



#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	//For blockAllocator Testing

	//The block allocator
	//Engine::BlockAllocator blockAllocator;

	//Creating the block allocator
	//blockAllocator.create(1024 * 1024, 100);
	//GetBlockAllocator(&blockAllocator);

	//The memory manager that handles FSA
	//Engine::FSAManager fsaManager;
	//GetFSAManager(&fsaManager);
	//fsaManager.CreateFSAs(&blockAllocator);
	


	//Run the float check unit test
	//FloatChecker_UnitTest();


	//Run the block allocator unit test
	//HeapManager_UnitTest();

	//Run the fsa unit test
	//FSA_UnitTest(&fsaManager);



	//Run the bit array unit test
	//BitArray_UnitTest();

	//_getch();


	/*


	

	
	//For Monster Chase
	srand(time_t(0));

	//Create reference to a game manager object
	GameManager* gameManager = new GameManager();

	//Initialize the game
	gameManager->InitializeGame();



	
	//Start of the main game loop
	do
	{
		gameManager->UpdateGameManager();

	}while (gameManager->ReadAdditionalInput() != 'q');


   
	delete gameManager;
	gameManager = nullptr;

	*/

	//{
	//	Monster m1("m1");

	//	// copy constructor
	//	Monster m2 = m1;

	//	//// copy assignment
	//	Monster m3("m3");
	//	m3 = m1;

	//	//// move constructor
	//	Monster m4 = std::move(m2);

	//	//// move assignment
	//	Monster m5("m5");
	//	m5 = std::move(m4);
	//}

	/*

	//Testing for Part 1



	//Test allocating memory
	for (int i = 0; i < 10; i++)
	{
		//blockAllocator._alloc(pow(16.0, i + 1));
		if (blockAllocator._alloc(32+i) != NULL)
		{
			blockAllocator.PrintBlockDescriptors();
			//Halt the operation
			_getch();
		}

		//Ran out of block descriptors
		else {



			

			//The case where the unused block descriptors are all used
			if (blockAllocator.unusedDescriptorsHeadGetter() == NULL)
				printf("There are no more unused block descriptors available\n");
			else
				printf("There is not more free memory available\n");
			_getch();
			break;
			
		}

	}

	*/
	
	//Testing for part 2
	/*
	char * pointersToTest[5];

	//Test allocating memory
	for (unsigned int i = 0; i < 5; i++)
	{
		size_t requestSize = 32 + i;
		pointersToTest[i] =reinterpret_cast<char *> (blockAllocator._alloc(requestSize));

		//blockAllocator._alloc(pow(16.0, i + 1));
		if (pointersToTest[i] != NULL)
		{
			for (unsigned int j = 0; j < requestSize; ++j)
			{
				pointersToTest[i][j] = i + 65;
			}
#ifdef _DEBUG
			blockAllocator.PrintBlockDescriptors();
#endif
			//Halt the operation
			_getch();
		}

		//Ran out of block descriptors
		else {

			//The case where the unused block descriptors are all used
			if (blockAllocator.unusedDescriptorsHeadGetter() == NULL)
				printf("There are no more unused block descriptors available\n");
			else
				printf("There is not more free memory available\n");
			_getch();
			break;

		}

	}

	for (unsigned int i = 0; i < 5; i++) {
		for (unsigned int j = 0; j < (32 + i); ++j)
		{
			pointersToTest[i][j] = 64;
		}
	
		blockAllocator._free(pointersToTest[i]);

		//blockAllocator.k++;

#ifdef _DEBUG
		blockAllocator.PrintBlockDescriptors();
#endif
		
		//Halt the operation
		_getch();
	}

	
	blockAllocator._alloc(36);
	
#ifdef _DEBUG
	blockAllocator.PrintBlockDescriptors();
#endif

	//Halt the operation
	_getch();

	blockAllocator.GarabageCollector();

#ifdef _DEBUG
	blockAllocator.PrintBlockDescriptors();
#endif
	//Halt the operation
	_getch();
	
	blockAllocator.destroy();
	

#if defined _DEBUG
_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return 0;
	
}
*/