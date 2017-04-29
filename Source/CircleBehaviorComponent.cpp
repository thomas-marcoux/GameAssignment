#include "CircleBehaviorComponent.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "Random.h"

bool CircleBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
{
	_radius = 0;
	_forceMultiplier = 100;
	if (initializers.radius)
		_radius = random(OCTOROK_RADIUS_MIN, OCTOROK_RADIUS_MAX);
	else
		_speed = random(OCTOROK_SPEED_MIN, OCTOROK_SPEED_MAX);
	_anchor = nullptr;
	_lever = nullptr;
	return true;
}

//Create Joints for circling Octorock
bool CircleBehaviorComponent::Initialize(ObjectFactory *oFactory)
{
	if (_radius)
	{
		GAME_VEC	object_pos = _owner->pDevice->GetPosition(_owner);
		GAME_VEC	anchor_pos = object_pos;
		anchor_pos.y -= _radius;

		GAME_VEC	lever_pos = anchor_pos;
		GAME_VEC	lever_anchorA = lever_pos;
		GAME_VEC	lever_anchorB = lever_pos;

		lever_anchorB.y += _radius;
		_anchor = oFactory->createAnchor(_owner, anchor_pos);
		_lever = oFactory->createLever(lever_pos, _radius);
		_owner->pDevice->createRevolvingJoint(_anchor.get(), _lever.get(), anchor_pos, lever_anchorA);
		_owner->pDevice->createRevolvingJoint(_owner, _lever.get(), object_pos, lever_anchorB);
	}
	return true;
}

std::unique_ptr<Object> CircleBehaviorComponent::Update(GAME_FLT dt)
{
	if (_radius)
	{
		_applyForce.x = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
		_applyForce.y = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
		_owner->pDevice->SetLinearVelocity(_owner, _applyForce);
	}
	else
		_owner->pDevice->SetAngle(_owner, _owner->pDevice->GetAngle(_owner) + _speed);
	return nullptr;
}

bool CircleBehaviorComponent::Finish()
{
	return false;
}
