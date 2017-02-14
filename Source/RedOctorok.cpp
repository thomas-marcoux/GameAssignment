#include "RedOctorok.h"

void RedOctorok::Update(GAME_FLT)
{
}

void RedOctorok::Draw(GAME_FLT p_angle, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, p_angle);
}
