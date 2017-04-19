#include "ArrowBehaviorComponent.h"
#include "BodyComponent.h"

bool ArrowBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
{
	_movement = (GAME_FLT)initializers.arrow_movement;
	_movementAngle = initializers.movement_angle;
	return true;
}

std::unique_ptr<Object> ArrowBehaviorComponent::Update(GAME_FLT dt)
{
	BodyComponent*	body = _owner->GetComponent<BodyComponent>();
	if (!body) return NULL;
	GAME_VEC position = body->getPosition();

	position.x += _movement * cos(_movementAngle);
	position.y -= _movement * sin(_movementAngle);
	body->setPosition(position);
	return NULL;
}
