#include "RedOctorok.h"
#include "Random.h"

RedOctorok::RedOctorok()
{
	movement = REDOCTOROK_MOVEMENT;
	movementAngle = TO_RADIAN(angle);
	radius = random(REDOCTOROK_RADIUS_MIN, REDOCTOROK_RADIUS_MAX);
}

//Update object's position
void RedOctorok::Update(GAME_FLT)
{
	movementAngle -= movement;
	position.x += -radius * cos(movementAngle);
	position.y += -radius * sin(movementAngle);
	if (movementAngle <= -PI2)
		movementAngle = 0;
	angle = TO_DEGREE(movementAngle)-90; //Adjusts angle so the octorok is facing forward
}

//Calls object's texture's draw method
void RedOctorok::Draw(GAME_FLT, View *p_view)
{
	texture->Draw(gDevice->getRenderer(), p_view, position, angle);
}
