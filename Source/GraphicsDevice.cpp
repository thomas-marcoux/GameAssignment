#include<iostream>
#include <algorithm>
#include "Definitions.h"
#include "GraphicsDevice.h"
#include "SpriteComponent.h"

//Calls shutdown method on object destruction
GraphicsDevice::~GraphicsDevice()
{
	if (!ShutDown())
	{
		std::cout << "SDL could not shut down. SDL_Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
}

//Initialize SDL components
bool GraphicsDevice::Initialize(bool fullScreen)
{
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL could not initialize. SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}
	//Initialize SDL_image subsystems
	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "SDL_image could not initialize. IMG_Init Error: " << IMG_GetError() << std::endl;
		return(false);
	}
	if (fullScreen)
	{
		screen = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		screen = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	}
	if (screen == NULL)
	{
		std::cout << "Window could not be created. SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}
	//Construct the renderer
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "Renderer could not be created. SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}
	//Set the background color
	SDL_SetRenderDrawColor(renderer, 244, 214, 159, 255);
	return true;
}

//Properly frees SDL components
bool GraphicsDevice::ShutDown()
{
	//Free the window
	SDL_DestroyWindow(screen);
	screen = NULL;
	//Free renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	//Quit SDL Subsystems
	IMG_Quit();
	SDL_Quit();
	return true;
}

//Clear renderer
void GraphicsDevice::Begin()
{
	SDL_RenderClear(renderer);
}

//Displays renderer
void GraphicsDevice::Present()
{
	SDL_RenderPresent(renderer);
}

//Draw each sprite
void GraphicsDevice::Draw(View* p_view)
{
	for (auto sprite : sprites)
		sprite->Draw(p_view);
}

//Returns renderer
SDL_Renderer* GraphicsDevice::getRenderer()
{
	return(renderer);
}

void GraphicsDevice::addSprite(SpriteComponent *sprite)
{
	sprites.push_back(sprite);
}

void GraphicsDevice::removeSprite(SpriteComponent* toRemove)
{
	sprites.erase(std::remove(sprites.begin(), sprites.end(), toRemove));
}
