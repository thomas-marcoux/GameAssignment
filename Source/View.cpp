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
	GAME_VEC	body = player->GetComponent<BodyComponent>()->getPosition();

	if (body.x - position.x <= DIST_TO_BORDER)
		center.x -= VIEW_MOVEMENT;
	if (position.x + SCREEN_WIDTH - body.x - SPRITE_WIDTH <= DIST_TO_BORDER)
		center.x += VIEW_MOVEMENT;
	if (body.y - position.y <= DIST_TO_BORDER)
		center.y -= VIEW_MOVEMENT;
	if (position.y + SCREEN_HEIGHT - body.y - SPRITE_HEIGHT <= DIST_TO_BORDER)
		center.y += VIEW_MOVEMENT;
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
