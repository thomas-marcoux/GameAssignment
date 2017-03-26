#include "CircleBehaviorComponent.h"
#include "Random.h"

bool CircleBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	if (initializers.radius)
	{
		movement = REDOCTOROK_MOVEMENT;
		movementAngle = TO_RADIAN(angle);
		_radius = random(REDOCTOROK_RADIUS_MIN, REDOCTOROK_RADIUS_MAX);
	}
	else
	{
		_radius = 0;
		movement = random(BLUEOCTOROK_MOVEMENT_MIN, BLUEOCTOROK_MOVEMENT_MAX);
	}
		
}

std::unique_ptr<Object> CircleBehaviorComponent::Update()
{
	if (_radius)
	{
		movementAngle -= movement;
		position.x += -_radius * cos(movementAngle);
		position.y += -_radius * sin(movementAngle);
		if (movementAngle <= -PI2)
			movementAngle = 0;
		angle = TO_DEGREE(movementAngle) - 90; //Adjusts angle so the octorok is facing forward
	}
	else
	{
		angle -= movement;
		if (angle <= -360.0)
			angle = 0;
	}
	return NULL;
}

bool CircleBehaviorComponent::Finish()
{
	return false;
}
