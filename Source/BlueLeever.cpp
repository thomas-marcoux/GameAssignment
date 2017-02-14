#include "BlueLeever.h"

void BlueLeever::Update(GAME_FLT)
{
}

void BlueLeever::Draw(GAME_FLT p_angle, View * p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, p_angle);
}
