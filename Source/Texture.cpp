#include "Definitions.h"
#include "Texture.h"

Texture::Texture() : width(SPRITE_WIDTH), height(SPRITE_HEIGHT), texture(NULL)
{}


Texture::~Texture()
{
	free();
}

//Loads image at specified path, returns false if an error occured.
bool Texture::load(SDL_Renderer* renderer, std::string path)
{
	//Destroy existing texture information
	free();
	SDL_Surface* surface = NULL;
	surface = IMG_Load(path.c_str());
	if (surface == NULL)
	{
		std::cout << "Unable to load image " << path.c_str() << ". IMG_Load Error: " << IMG_GetError() << std::endl;
		return false;
	}
	//Color key image
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
	//Create an optimized image
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		std::cout << "Unable to create texture from image " << path.c_str() << ". SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	//Set the height and width from the texture
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	//Free the loaded image; no longer needed
	SDL_FreeSurface(surface);
	return (texture != NULL);
}


void Texture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

int Texture::getWidth()
{
	return width;
}


int Texture::getHeight()
{
	return height;
}

void Texture::Draw(SDL_Renderer * renderer, View * view, GAME_VEC position, GAME_FLT angle, SDL_Rect * clip)
{
	SDL_Rect	rect = { 0, 0, width, height };
	if (clip)
	{
		rect.x = clip->x;
		rect.y = clip->y;
	}
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);
}
