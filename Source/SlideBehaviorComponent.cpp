#include "SlideBehaviorComponent.h"
#include "Object.h"
#include "Random.h"

bool SlideBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
{
	_vertical = initializers.vertical;
	_forceMultiplier = 100;
	_startPosition = initializers.pos;
	_maxDistance = (GAME_FLT)random(LEEVER_MIN_DISTANCE, LEEVER_MAX_DISTANCE);
	return true;
}
#include <iostream>
std::unique_ptr<Object> SlideBehaviorComponent::Update(GAME_FLT dt)
{
	GAME_VEC position = _owner->pDevice->GetPosition(_owner);

	if (_vertical)
	{
		if (abs(position.y - _startPosition.y) >= _maxDistance)
		{
			_owner->pDevice->SetAngle(_owner, _owner->pDevice->GetAngle(_owner) + 180.0f);
			//std::cout << "x = " << position.x << " y = " << position.y <<  "max = " << abs(position.x - _startPosition.x) << std::endl;
		}
		_applyForce.x = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
		_applyForce.y = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
	}
	else
	{
		//std::cout << "x = " << position.x << " y = " << position.y << " start x = " << _startPosition.x << " y = " << _startPosition.y << std::endl;
		if (abs(position.x - _startPosition.x) >= _maxDistance)
		{
			_owner->pDevice->SetAngle(_owner, _owner->pDevice->GetAngle(_owner) + 180.0f);
			//std::cout << "x = " << position.x << " y = " << position.y << "max = " << abs(position.x - _startPosition.x) << std::endl;
		}
		_applyForce.x = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
		_applyForce.y = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
	}
	_owner->pDevice->SetLinearVelocity(_owner, _applyForce);
	return NULL;
}
