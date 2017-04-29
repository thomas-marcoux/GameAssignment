#include "SlideBehaviorComponent.h"
#include "Object.h"
#include "Random.h"

bool SlideBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
{
	_vertical = initializers.vertical;
	_forceMultiplier = 100;
	_startPosition = initializers.pos;
	_maxDistance = (GAME_FLT)random(LEEVER_MIN_DISTANCE, LEEVER_MAX_DISTANCE);
	_forward = true;
	return true;
}

std::unique_ptr<Object> SlideBehaviorComponent::Update(GAME_FLT dt)
{
	checkDistance();
	if (_vertical)
	{
		if (_forward)
		{
			_applyForce.x = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
			_applyForce.y = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
		}
		else
		{
			_applyForce.x = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) + (PI / 2))*_forceMultiplier;
			_applyForce.y = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) + (PI / 2))*_forceMultiplier;
		}
	}
	else
	{
		if (_forward)
		{
			_applyForce.x = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
			_applyForce.y = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
		}
		else
		{
			_applyForce.x = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) + (PI / 2))*_forceMultiplier;
			_applyForce.y = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) + (PI / 2))*_forceMultiplier;
		}
	}
	_owner->pDevice->SetLinearVelocity(_owner, _applyForce);
	return nullptr;
}

//Turn around
void SlideBehaviorComponent::turn()
{
	_forward = !_forward;
}

//Calls turn if enough distance has been traveled
void SlideBehaviorComponent::checkDistance()
{
	GAME_VEC position = _owner->pDevice->GetPosition(_owner);

	if (abs(position.y - _startPosition.y) >= _maxDistance || abs(position.x - _startPosition.x) >= _maxDistance)
		turn();
}
