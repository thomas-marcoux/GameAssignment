#include "PlayerInputComponent.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "TimedLifeComponent.h"
#include "ArrowBehaviorComponent.h"

bool PlayerInputComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	return false;
}

bool PlayerInputComponent::Initialize(InputDevice *iD)
{
	iDevice = iD;
	_textures.assign(NB_TEXTURES, NULL);
	return true;
}

bool PlayerInputComponent::LoadTexture(TEXTURE_ID id, std::shared_ptr<Texture> texture)
{
	_textures[id] = texture;
	return true;
}

std::unique_ptr<Object> PlayerInputComponent::Update()
{
	std::shared_ptr<BodyComponent> body = _owner->GetComponent<BodyComponent>();
	if (!body) return NULL;
	GAME_VEC p = body->getPosition();
	GAME_FLT angle = body->getAngle();

	UpdateTexture();
	iDevice->Update();
	if (iDevice->GetEvent(GAME_UP))
	{
		angle = LINK_UP;
		p.x -= LINK_MOVEMENT * cos(angle);
		p.y -= LINK_MOVEMENT * sin(angle);
	}
	if (iDevice->GetEvent(GAME_LEFT))
	{
		angle = LINK_LEFT;
		p.x += LINK_MOVEMENT * cos(angle);
		p.y += LINK_MOVEMENT * sin(angle);
	}
	if (iDevice->GetEvent(GAME_DOWN))
	{
		angle = LINK_DOWN;
		p.x -= LINK_MOVEMENT * cos(angle);
		p.y -= LINK_MOVEMENT * sin(angle);
	}
	if (iDevice->GetEvent(GAME_RIGHT))
	{
		angle = LINK_RIGHT;
		p.x += LINK_MOVEMENT * cos(angle);
		p.y += LINK_MOVEMENT * sin(angle);
	}
	if (iDevice->GetEvent(GAME_SPACE))
	{
		return CreateArrow();
	}
	body->setPosition(p);
	body->setAngle(angle);
	return NULL;
}

void PlayerInputComponent::UpdateTexture()
{
	std::shared_ptr<BodyComponent>	body = _owner->GetComponent<BodyComponent>();
	std::shared_ptr<SpriteComponent> sprite = _owner->GetComponent<SpriteComponent>();

	if (!body || !sprite) return;
	GAME_FLT angle = body->getAngle();

	if (angle == LINK_DOWN)
		sprite->setTexture(_textures[LINK_TEXTURE_DOWN]);
	else if (angle == LINK_RIGHT)
		sprite->setTexture(_textures[LINK_TEXTURE_RIGHT]);
	else if (angle == LINK_LEFT)
		sprite->setTexture(_textures[LINK_TEXTURE_LEFT]);
	else
		sprite->setTexture(_textures[LINK_TEXTURE_UP]);
}

bool PlayerInputComponent::Finish()
{
	return false;
}

std::unique_ptr<Object> PlayerInputComponent::CreateArrow()
{
	std::unique_ptr<Object> object = std::make_unique<Object>();
	std::shared_ptr<BodyComponent> body = std::make_shared<BodyComponent>(object);
	/*
	std::shared_ptr<SpriteComponent> sprite = std::make_shared<SpriteComponent>(object);
	std::shared_ptr<TimedLifeComponent> tlc = std::make_shared<TimedLifeComponent>(object);
	std::shared_ptr<ArrowBehaviorComponent> arrow = std::make_shared<ArrowBehaviorComponent>(object);
	std::shared_ptr<BodyComponent>	link_body = _owner->GetComponent<BodyComponent>();
	std::shared_ptr<SpriteComponent>	link_sprite = _owner->GetComponent<SpriteComponent>();

	body->setPosition(link_body->getPosition());
	body->setAngle(link_body->getAngle());
	sprite->Initialize(link_sprite->getGDevice(), _textures[TEXTURE_ARROW]);
	tlc->Initialize(ARROW_HEALTH, ARROW_HEALTH_DECREMENT);
	arrow->Initialize(ARROW_MOVEMENT);
	*/
	object->addComponent(std::move(body));
	/*
	object->addComponent(std::move(sprite));
	object->addComponent(std::move(tlc));
	object->addComponent(std::move(arrow));
	*/
	return std::move(object);
}
