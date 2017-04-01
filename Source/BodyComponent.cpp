#include "BodyComponent.h"

BodyComponent::BodyComponent(std::unique_ptr<Object> const& owner) : Component(owner)
{

}

bool BodyComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	_startPosition = initializers.pos;
	_position = _startPosition;
	_angle = initializers.angle;
	return true;
}
