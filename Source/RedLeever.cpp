#include "RedLeever.h"

//Update object's position
void RedLeever::Update(GAME_FLT)
{
	position.x += (int)movement;
	if (abs(position.x - startPosition.x) >= MAX_DISTANCE)
		movement *= -1.0;
}

//Calls object's texture's draw method
void RedLeever::Draw(GAME_FLT, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}
