#include "BlueOctorok.h"

void BlueOctorok::Update(GAME_FLT)
{
}

void BlueOctorok::Draw(GAME_FLT p_angle, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, p_angle);
}
