#include "TimedLifeComponent.h"

TimedLifeComponent::TimedLifeComponent(std::shared_ptr<Object> owner) : Component(owner)
{
	_health = 0;
}

bool TimedLifeComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	return true;
}

bool TimedLifeComponent::Initialize(GAME_INT health, GAME_INT decrement)
{
	_health = health;
	_decrement = decrement;
	return true;
}

std::unique_ptr<Object> TimedLifeComponent::Update()
{
	_health -= _decrement;
	return NULL;
}

bool TimedLifeComponent::Finish()
{
	return (_health <= 0) ? true : false;
}
