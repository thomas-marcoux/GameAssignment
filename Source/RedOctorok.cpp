#include "RedOctorok.h"

void RedOctorok::Update(GAME_FLT)
{
	angle += movement;
	position.x += radius * cos(angle);
	position.y += radius * sin(angle);
}

void RedOctorok::Draw(GAME_FLT, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}
