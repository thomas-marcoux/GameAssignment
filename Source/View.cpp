#include "View.h"

bool View::Initialize(InputDevice *i, GAME_FLT x, GAME_FLT y)
{
	iDevice = i;
	position.x = x;
	position.y = y;
	return true;
}

bool View::Update(GAME_FLT gameTime)
{

	return true;
}
