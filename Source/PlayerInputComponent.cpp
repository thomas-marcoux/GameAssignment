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

std::unique_ptr<Object> PlayerInputComponent::Update()
{
	BodyComponent* body = _owner->GetComponent<BodyComponent>();
	GAME_VEC p = body->getPosition();
	GAME_FLT angle = body->getAngle();

	_owner->GetComponent<SpriteComponent>()->UpdateTexture();
	iDevice->Update();
	if (iDevice->GetEvent(GAME_UP))
	{
		angle = FACE_UP;
		p.y -= LINK_MOVEMENT * sin(angle);
	}
	if (iDevice->GetEvent(GAME_DOWN))
	{
		angle = FACE_DOWN;
		p.y -= LINK_MOVEMENT * sin(angle);
	}
	if (iDevice->GetEvent(GAME_LEFT))
	{
		angle = FACE_LEFT;
		p.x += LINK_MOVEMENT * cos(angle);
	}
	if (iDevice->GetEvent(GAME_RIGHT))
	{
		angle = FACE_RIGHT;
		p.x += LINK_MOVEMENT * cos(angle);
	}
	if (iDevice->GetEvent(GAME_SPACE))
		return oFactory->createArrow(_owner);
	body->setPosition(p);
	body->setAngle(angle);
	return nullptr;
}

bool PlayerInputComponent::Finish()
{
	return false;
}

