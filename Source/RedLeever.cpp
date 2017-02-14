#include "RedLeever.h"

void RedLeever::Update(GAME_FLT)
{
}

void RedLeever::Draw(GAME_FLT p_angle, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, p_angle);
}
