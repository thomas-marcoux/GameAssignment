#include "TimedLifeComponent.h"
#include "BombBehaviorComponent.h"

TimedLifeComponent::TimedLifeComponent(std::unique_ptr<Object> const&  owner) : Component(owner)
{

}

bool TimedLifeComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
{
	_health = initializers.timer;
	_decrement = initializers.timer_speed;
	return true;
}

std::unique_ptr<Object> TimedLifeComponent::Update(GAME_FLT dt)
{
	_health -= _decrement;
	return nullptr;
}

bool TimedLifeComponent::Finish()
{
	if (_health > 0)
		return false;
	BombBehaviorComponent*	bomb = _owner->GetComponent<BombBehaviorComponent>();
	if (_health <= 0 && !bomb)
		return true;
	bomb->blast();
	return true;
}
