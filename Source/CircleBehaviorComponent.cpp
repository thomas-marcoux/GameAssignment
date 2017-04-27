#include "CircleBehaviorComponent.h"
#include "BodyComponent.h"
#include "Object.h"
#include "Random.h"

bool CircleBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
{
	if (initializers.radius)
	{
		//create physics joint anchor?
		_movement = REDOCTOROK_MOVEMENT;
		_movementAngle = TO_RADIAN(initializers.angle);
		_radius = random(REDOCTOROK_RADIUS_MIN, REDOCTOROK_RADIUS_MAX);
	}
	else
	{
		_radius = 0;
		_movement = random(BLUEOCTOROK_MOVEMENT_MIN, BLUEOCTOROK_MOVEMENT_MAX);
	}
	return true;
}
#include<iostream>
std::unique_ptr<Object> CircleBehaviorComponent::Update(GAME_FLT dt)
{
	BodyComponent*	body = _owner->GetComponent<BodyComponent>();
	if (!body) return NULL;
	GAME_VEC position = body->getPosition();
	GAME_FLT angle = body->getAngle();

	if (_radius)
	{
		GAME_VEC applyForce;
		GAME_INT forceMultiplier = 100;
		applyForce.x = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*forceMultiplier;
		applyForce.y = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*forceMultiplier;
		_owner->pDevice->SetAngularVelocity(_owner, _owner->pDevice->GetAngularVelocity(_owner) + 2.0f * dt);
		_owner->pDevice->SetLinearVelocity(_owner, applyForce);
		_movementAngle -= _movement;
		position.x += -_radius * cos(_movementAngle);
		position.y += -_radius * sin(_movementAngle);
		if (_movementAngle <= -PI2)
			_movementAngle = 0;
		angle = TO_DEGREE(_movementAngle) - 90; //Adjusts angle so the octorok is facing forward
		body->setPosition(position);
	}
	else
	{
		_owner->pDevice->SetTorque(_owner, 20.0f * dt);
		//_owner->pDevice->SetAngularVelocity(_owner, 20.0f);
		//_owner->pDevice->SetAngularVelocity(_owner, _owner->pDevice->GetAngularVelocity(_owner) + 2.0f * dt);
		/*
		angle -= _movement;
		if (angle <= -360.0)
			angle = 0;
		*/
	}
	body->setAngle(angle);
	return nullptr;
}

bool CircleBehaviorComponent::Finish()
{
	return false;
}
