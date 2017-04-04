#include "ArrowBehaviorComponent.h"
#include "BodyComponent.h"

bool ArrowBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
{
	_movement = initializers.arrow_movement;
	return true;
}

std::unique_ptr<Object> ArrowBehaviorComponent::Update()
{
	BodyComponent*	body = _owner->GetComponent<BodyComponent>();
	if (!body) return NULL;
	GAME_VEC position = body->getPosition();
	GAME_FLT angle = body->getAngle();

	position.x += _movement * cos(angle);
	position.y -= _movement * sin(angle);
	body->setPosition(position);
	return NULL;
}
