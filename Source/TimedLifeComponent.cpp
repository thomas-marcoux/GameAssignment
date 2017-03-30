#include "TimedLifeComponent.h"

TimedLifeComponent::TimedLifeComponent(std::shared_ptr<Object> owner) : Component(owner)
{
	health = ARROW_HEALTH;
}

bool TimedLifeComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	return true;
}

std::unique_ptr<Object> TimedLifeComponent::Update()
{
	health -= ARROW_TRAVEL;
	return NULL;
}

bool TimedLifeComponent::Finish()
{
	return (health <= 0) ? true : false;
}
