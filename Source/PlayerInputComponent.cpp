#include "PlayerInputComponent.h"
#include "BodyComponent.h"

bool PlayerInputComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	return false;
}

bool PlayerInputComponent::Initialize(InputDevice *iD)
{
	iDevice = iD;
	return true;
}

std::unique_ptr<Object> PlayerInputComponent::Update()
{
	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();
	if (!body) return NULL;
	GAME_VEC p = body->getPosition();
	GAME_FLT angle = body->getAngle();

	iDevice->Update();
	if (iDevice->GetEvent(GAME_UP))
	{
		p.x -= LINK_MOVEMENT * sin(angle);
		p.y -= LINK_MOVEMENT * cos(angle);
	}
	if (iDevice->GetEvent(GAME_LEFT))
		angle -= LINK_ROTATION;
	if (iDevice->GetEvent(GAME_DOWN))
	{
		p.x += LINK_MOVEMENT * sin(angle);
		p.y += LINK_MOVEMENT * cos(angle);
	}
	if (iDevice->GetEvent(GAME_RIGHT))
		angle += LINK_ROTATION;
	body->setPosition(p);
	body->setAngle(angle);
	return NULL;
}

bool PlayerInputComponent::Finish()
{
	return false;
}
