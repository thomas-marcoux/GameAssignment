#include "RedLeever.h"

void RedLeever::Update(GAME_FLT)
{
	position.y += (int)movement;
	if (abs(position.y - startPosition.y) >= MAX_DISTANCE)
		movement *= -1.0;
}

void RedLeever::Draw(GAME_FLT, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}
