#include "SlideBehaviorComponent.h"
#include "Random.h"

bool SlideBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	_vertical = initializers.vertical;
	_movement = LEEVER_MOVEMENT;
	_maxDistance = random(LEEVER_MIN_DISTANCE, LEEVER_MAX_DISTANCE);
	return true;
}

std::unique_ptr<Object> SlideBehaviorComponent::Update()
{
	if (_vertical)
	{
		position.y += (int)movement;
		if (abs(position.y - startPosition.y) >= maxDistance)
			movement *= -1.0;
	}
	else
	{
		position.x += (int)movement;
		if (abs(position.x - startPosition.x) >= maxDistance)
			movement *= -1.0;
	}
	return NULL;
}
