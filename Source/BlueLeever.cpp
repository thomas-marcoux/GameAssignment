#include "BlueLeever.h"

void BlueLeever::Update(GAME_FLT)
{
	position.x += (int)movement;
	if (abs(position.x - startPosition.x) >= MAX_DISTANCE)
		movement *= -1.0;
}

void BlueLeever::Draw(GAME_FLT, View * p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}
