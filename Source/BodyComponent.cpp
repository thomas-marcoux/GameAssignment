#include "BodyComponent.h"

bool BodyComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	_startPosition = initializers.pos;
	_position = _startPosition;
	_angle = initializers.angle;
	return true;
}
