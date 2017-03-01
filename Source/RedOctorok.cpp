#include "RedOctorok.h"

void RedOctorok::Update(GAME_FLT)
{
	angle += movement;
	position.x += radius * cos(angle);
	position.y += radius * sin(angle);
	if (angle >= 360.0)
		angle = 0;
}

void RedOctorok::Draw(GAME_FLT, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}
