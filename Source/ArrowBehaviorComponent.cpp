#include "ArrowBehaviorComponent.h"
#include "BodyComponent.h"

bool ArrowBehaviorComponent::Initialize(GAME_INT movement)
{
	_movement = movement;
	return true;;
}

std::unique_ptr<Object> ArrowBehaviorComponent::Update()
{
	BodyComponent*	body = _owner->GetComponent<BodyComponent>();
	if (!body) return NULL;
	GAME_VEC position = body->getPosition();

	position.x += (int)_movement;
	body->setPosition(position);
	return NULL;
}
