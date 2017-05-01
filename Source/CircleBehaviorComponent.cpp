#include "CircleBehaviorComponent.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "Random.h"

//Initializes and randomizes attributes
bool CircleBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
{
	_radius = 0;
	_forceMultiplier = DEFAULT_FORCE_MULTIPLIER;
	if (initializers.radius)
		_radius = random(OCTOROK_RADIUS_MIN, OCTOROK_RADIUS_MAX);
	_speed = random(OCTOROK_SPEED_MIN, OCTOROK_SPEED_MAX);
	_anchor = nullptr;
	_lever = nullptr;
	return true;
}

//Create the joints needed to rotate the object, one anchor and one lever if blue octorok
bool CircleBehaviorComponent::Initialize(ObjectFactory *oFactory)
{
	GAME_VEC	object_pos = _owner->pDevice->GetPosition(_owner);
	GAME_VEC	anchor_pos = object_pos;

	if (_radius)
	{
		anchor_pos.y -= _radius;
		_anchor = oFactory->createAnchor(anchor_pos);
		_lever = oFactory->createLever(anchor_pos, _radius);
		_owner->pDevice->createRevolvingJoint(_anchor.get(), _lever.get(), anchor_pos, anchor_pos);
		_owner->pDevice->createRevolvingJoint(_owner, _lever.get(), object_pos, object_pos);
	}
	else
	{
		_anchor = oFactory->createAnchor(anchor_pos);
		_owner->pDevice->createRevolvingJoint(_anchor.get(), _owner, false, { 0, 0 }, { 0,0 }, 0, false, 0, 0, true, _speed, 100.0f);
	}
	return true;
}

std::unique_ptr<Object> CircleBehaviorComponent::Update(GAME_FLT dt)
{
	_applyForce.x = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
	_applyForce.y = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
	_owner->pDevice->SetLinearVelocity(_owner, _applyForce);
	_owner->pDevice->SetAngularVelocity(_owner, _speed);
	return nullptr;
}

bool CircleBehaviorComponent::Finish()
{
	return false;
}
