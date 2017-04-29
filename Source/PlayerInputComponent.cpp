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
	_forceMultiplier = 100;
	return true;
}

std::unique_ptr<Object> PlayerInputComponent::Update(GAME_FLT dt)
{
	BodyComponent* body = _owner->GetComponent<BodyComponent>();
	SpriteComponent* sprite = _owner->GetComponent<SpriteComponent>();
	GAME_FLT angle = body->getAngle();
	GAME_VEC applyForce;

	iDevice->Update();
	applyForce.x = 0.0f;
	applyForce.y = 0.0f;
	if (iDevice->GetEvent(GAME_UP))
	{
		sprite->UpdateTexture(TEXTURE_UP);
		applyForce.x = (float)cosf(ANGLE_UP - (PI / 2))*_forceMultiplier;
		applyForce.y = (float)sinf(ANGLE_UP - (PI / 2))*_forceMultiplier;
	}
	if (iDevice->GetEvent(GAME_DOWN))
	{
		sprite->UpdateTexture(TEXTURE_DOWN);
		applyForce.x = (float)cosf(ANGLE_DOWN - (PI / 2))*_forceMultiplier;
		applyForce.y = (float)sinf(ANGLE_DOWN - (PI / 2))*_forceMultiplier;
	}
	if (iDevice->GetEvent(GAME_LEFT))
	{
		sprite->UpdateTexture(TEXTURE_LEFT);
		applyForce.x = (float)cosf(ANGLE_LEFT - (PI / 2))*_forceMultiplier;
		applyForce.y = (float)sinf(ANGLE_LEFT - (PI / 2))*_forceMultiplier;
	}
	if (iDevice->GetEvent(GAME_RIGHT))
	{
		sprite->UpdateTexture(TEXTURE_RIGHT);
		applyForce.x = (float)cosf(ANGLE_RIGHT - (PI / 2))*_forceMultiplier;
		applyForce.y = (float)sinf(ANGLE_RIGHT - (PI / 2))*_forceMultiplier;
	}
	if (iDevice->GetEvent(GAME_SPACE))
	{
		if (!_owner->hasChild())
			return oFactory->createArrow(_owner);
	}
	_owner->pDevice->SetLinearVelocity(_owner, applyForce);
	body->setAngle(angle);
	_owner->pDevice->SetAngle(_owner, TO_DEGREE(ANGLE_UP)); //Ensures the axis sprites do not rotate and remain aligned
	return nullptr;
}

bool PlayerInputComponent::Finish()
{
	return false;
}

