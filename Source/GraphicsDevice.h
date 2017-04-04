#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "View.h"

class SpriteComponent;

//SDL graphics rendering class
class GraphicsDevice
{
public:
	GraphicsDevice() : screen(NULL), renderer(NULL) {}
	~GraphicsDevice();
	bool Initialize(bool);
	bool ShutDown();
	void Begin();
	void Present();
	void Draw(View*);
	SDL_Renderer* getRenderer();
	void addSprite(SpriteComponent*);
	void removeSprite(SpriteComponent*);

private:
	//Window(s) to display graphics
	SDL_Window* screen;
	SDL_Renderer* renderer;
	std::vector<SpriteComponent*>	sprites;
};

#endif // !GRAPHICSDEVICE_H
