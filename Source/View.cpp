#include "View.h"

bool View::Initialize(InputDevice *i, GAME_FLT x, GAME_FLT y)
{
	iDevice = i;
	center.x = x;
	center.y = y;
	position.x = x;
	position.y = y;
	return true;
}

bool View::Update(GAME_FLT gameTime)
{
	switch (iDevice->GetEvent())
	{
	case GAME_UP:
		position.y -= 2; break;
	case GAME_DOWN:
		position.y += 2; break;
	case GAME_LEFT:
		position.x -= 2; break;
	case GAME_RIGHT:
		position.x += 2; break;
	case GAME_ESC:
		return false;
	case GAME_QUIT:
		return false;
	}
	return true;
}
