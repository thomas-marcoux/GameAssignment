#include "BlueOctorok.h"

void BlueOctorok::Update(GAME_FLT)
{
	angle += movement;
}

void BlueOctorok::Draw(GAME_FLT, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}
