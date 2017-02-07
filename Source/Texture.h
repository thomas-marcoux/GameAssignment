#ifndef TEXTURE_H
#define TEXTURE_H

#include "View.h"

class Texture
{
public:
	Texture() {}
	~Texture() {}
	void Draw(SDL_Renderer* renderer, View* view, GAME_VEC position, GAME_FLT angle,
		SDL_Rect* clip = nullptr);
private:

};

#endif // !TEXTURE_H
