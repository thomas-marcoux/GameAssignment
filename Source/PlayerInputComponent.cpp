#include "PlayerInputComponent.h"
#include "BodyComponent.h"
#include "InputDevice.h"
#include "ObjectFactory.h"
#include "SpriteComponent.h"
#include "View.h"

PlayerInputComponent::PlayerInputComponent(std::unique_ptr<Object> const& owner) : Component(owner)
{

}

bool PlayerInputComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
{
	return true;
}

bool PlayerInputComponent::Initialize(InputDevice *iD, ObjectFactory* oF, View* v)
{
	iDevice = iD;
	oFactory = oF;
	view = v;
	view->setPlayer(_owner);
	return true;
}

std::unique_ptr<Object> PlayerInputComponent::Update(GAME_FLT dt)
{
	BodyComponent* body = _owner->GetComponent<BodyComponent>();
	GAME_FLT angle = body->getAngle();
	GAME_INT forceMultiplier = 100;
	GAME_VEC applyForce;

	_owner->GetComponent<SpriteComponent>()->UpdateTexture();
	iDevice->Update();
	if (iDevice->GetEvent(GAME_UP))
	{
		angle = FACE_UP;
		applyForce.x = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*forceMultiplier;
		applyForce.y = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*forceMultiplier;
		_owner->pDevice->SetLinearVelocity(_owner, applyForce);
	}
	if (iDevice->GetEvent(GAME_DOWN))
	{
		angle = FACE_DOWN;
		applyForce.x = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) + (PI / 2))*forceMultiplier;
		applyForce.y = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) + (PI / 2))*forceMultiplier;
		_owner->pDevice->SetLinearVelocity(_owner, applyForce);
	}
	if (iDevice->GetEvent(GAME_LEFT))
	{
		angle = FACE_LEFT;
		applyForce.x = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*forceMultiplier;
		applyForce.y = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*forceMultiplier;
		_owner->pDevice->SetLinearVelocity(_owner, applyForce);
	}
	if (iDevice->GetEvent(GAME_RIGHT))
	{
		angle = FACE_RIGHT;
		applyForce.x = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) + (PI / 2))*forceMultiplier;
		applyForce.y = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) + (PI / 2))*forceMultiplier;
		_owner->pDevice->SetLinearVelocity(_owner, applyForce);
	}
	if (iDevice->GetEvent(GAME_SPACE))
	{
		if (!_owner->hasChild())
			return oFactory->createArrow(_owner);
	}

	body->setAngle(angle);
	return nullptr;
}

bool PlayerInputComponent::Finish()
{
	return false;
}

