#include "BlueOctorok.h"

void BlueOctorok::Update(GAME_FLT)
{
	angle += movement;
	if (angle >= 360.0)
		angle = 0;
}

void BlueOctorok::Draw(GAME_FLT, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}
