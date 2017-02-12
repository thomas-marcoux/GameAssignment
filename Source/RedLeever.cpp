#include "RedLeever.h"

void RedLeever::Update(GAME_FLT)
{
}

void RedLeever::Draw(GAME_FLT p_angle, View *p_view)
{
	SDL_Rect	clip;

	clip.x = position.x;
	clip.y = position.y;
	texture->Draw(gDevice->getRenderer(), p_view, position, p_angle, &clip);
}
