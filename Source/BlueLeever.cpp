#include "BlueLeever.h"

//Update object position
void BlueLeever::Update(GAME_FLT)
{
	position.y += (int)movement;
	if (abs(position.y - startPosition.y) >= MAX_DISTANCE)
		movement *= -1.0;
}

//Calls object's texture's draw method
void BlueLeever::Draw(GAME_FLT, View * p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}
