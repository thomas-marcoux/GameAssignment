#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "Definitions.h"
#include "SDL.h"
#include "SDL_image.h"

class View;

//SDL texture class, will draw texture to the renderer
class Texture
{
public:
	Texture();
	~Texture();
	bool load(SDL_Renderer*, std::string);
	void free();
	int getWidth();
	int getHeight();
	void Draw(SDL_Renderer*, View*, GAME_VEC, GAME_FLT, SDL_Rect* = nullptr);

private:
	SDL_Texture* texture;
	int width;
	int height;
};

#endif // !TEXTURE_H
