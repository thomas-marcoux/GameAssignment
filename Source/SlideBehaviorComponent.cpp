#include "SlideBehaviorComponent.h"
#include "BodyComponent.h"
#include "Object.h"
#include "Random.h"

bool SlideBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
{
	_vertical = initializers.vertical;
	_movement = LEEVER_MOVEMENT;
	_maxDistance = random(LEEVER_MIN_DISTANCE, LEEVER_MAX_DISTANCE);
	return true;
}

std::unique_ptr<Object> SlideBehaviorComponent::Update()
{
	BodyComponent*	body = _owner->GetComponent<BodyComponent>();
	if (!body) return NULL;
	GAME_VEC position = body->getPosition();
	GAME_VEC startPosition = body->getStartPosition();

	if (_vertical)
	{
		position.y += (int)_movement;
		if (abs(position.y - startPosition.y) >= _maxDistance)
			_movement *= -1.0;
	}
	else
	{
		position.x += (int)_movement;
		if (abs(position.x - startPosition.x) >= _maxDistance)
			_movement *= -1.0;
	}
	body->setPosition(position);
	return NULL;
}
