#include "TimedLifeComponent.h"

TimedLifeComponent::TimedLifeComponent(std::unique_ptr<Object> const&  owner) : Component(owner)
{

}

bool TimedLifeComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
{
	_health = initializers.arrow_health;
	_decrement = initializers.arrow_decrement;
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
