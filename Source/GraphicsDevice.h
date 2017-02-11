#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include "SDL.h"
#include "SDL_image.h"

#define WINDOW_NAME "Quest1"

class GraphicsDevice
{
public:
	GraphicsDevice() : screen(NULL), renderer(NULL) {}
	~GraphicsDevice();
	bool Initialize(bool);
	bool ShutDown();
	void Begin();
	void Present();
	SDL_Renderer* getRenderer();

private:
	//Window(s) to display graphics
	SDL_Window* screen;
	SDL_Renderer* renderer;
};

#endif // !GRAPHICSDEVICE_H
