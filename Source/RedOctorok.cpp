#include "RedOctorok.h"

//Update object's position
void RedOctorok::Update(GAME_FLT)
{
	angle -= movement;
	position.x += -5*radius * cos(angle);
	position.y += -5*radius * sin(angle);
	if (angle <= -360.0)
		angle = 0;
}

//Calls object's texture's draw method
void RedOctorok::Draw(GAME_FLT, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}
