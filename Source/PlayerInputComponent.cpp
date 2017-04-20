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
	GAME_INT forceMultiplier = 1500;
	GAME_VEC applyForce;

	_owner->GetComponent<SpriteComponent>()->UpdateTexture();
	iDevice->Update();
	if (iDevice->GetEvent(GAME_UP))
	{
		angle = FACE_UP;
		//_owner->pDevice->SetLinearVelocity(_owner, _owner->pDevice->GetLinearVelocity(_owner));
		applyForce.x = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*forceMultiplier;
		applyForce.y = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*forceMultiplier;
		//_owner->pDevice->SetLinearVelocity(_owner, applyForce);
		_owner->pDevice->SetLinearImpulse(_owner, applyForce, _owner->pDevice->GetPosition(_owner));
		//p.y -= LINK_MOVEMENT * sin(angle);
	}
	if (iDevice->GetEvent(GAME_DOWN))
	{
		angle = FACE_DOWN;
		//p.y -= LINK_MOVEMENT * sin(angle);
	}
	if (iDevice->GetEvent(GAME_LEFT))
	{
		angle = FACE_LEFT;
		//p.x += LINK_MOVEMENT * cos(angle);
		_owner->pDevice->SetAngularVelocity(_owner, _owner->pDevice->GetAngularVelocity(_owner) - 2.0f * dt);
	}
	if (iDevice->GetEvent(GAME_RIGHT))
	{
		angle = FACE_RIGHT;
		//p.x += LINK_MOVEMENT * cos(angle);
		_owner->pDevice->SetAngularVelocity(_owner, _owner->pDevice->GetAngularVelocity(_owner) + 2.0f * dt);
	}
	if (iDevice->GetEvent(GAME_SPACE))
		return oFactory->createArrow(_owner);
	body->setAngle(angle);
	return nullptr;
}

bool PlayerInputComponent::Finish()
{
	return false;
}

