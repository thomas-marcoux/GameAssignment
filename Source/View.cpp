#include "View.h"
#include "Object.h"
#include "BodyComponent.h"

//Initializes View attributes
bool View::Initialize(InputDevice *i, GAME_FLT x, GAME_FLT y)
{
	iDevice = i;
	position.x = x;
	position.y = y;
	center.x = x + SCREEN_WIDTH_2;
	center.y = y + SCREEN_HEIGHT_2;
	angle = DEFAULT_VIEW_ANGLE;
	return true;
}

//Update view according to the game event
bool View::Update(GAME_FLT gameTime)
{
	iDevice->Update();
	if (iDevice->GetEvent(GAME_W))
	{
		center.x -= VIEW_MOVEMENT * sin(angle);
		center.y -= VIEW_MOVEMENT * cos(angle);
	}
	if (iDevice->GetEvent(GAME_S))
	{
		center.x += VIEW_MOVEMENT * sin(angle);
		center.y += VIEW_MOVEMENT * cos(angle);
	}
	if (iDevice->GetEvent(GAME_D))
		angle += VIEW_ROTATION;
	if (iDevice->GetEvent(GAME_A))
		angle -= VIEW_ROTATION;
	if (iDevice->GetEvent(GAME_ESC) || iDevice->GetEvent(GAME_QUIT))
		return false;
	position.x = center.x - SCREEN_WIDTH_2;
	position.y = center.y - SCREEN_HEIGHT_2;
	return true;
}
