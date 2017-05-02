#include "BombBehaviorComponent.h"
#include "ObjectFactory.h"
#include "SpriteComponent.h"
#include "TimedLifeComponent.h"
#include "SoundDevice.h"

bool BombBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const & initializers)
{
	return true;
}

bool BombBehaviorComponent::Initialize(ObjectFactory* oF, SoundDevice *sd)
{
	oFactory = oF;
	sDevice = sd;
	return true;
}

std::unique_ptr<Object> BombBehaviorComponent::Update(GAME_FLT)
{
	TimedLifeComponent*	timer = _owner->GetComponent<TimedLifeComponent>();

	if (timer->getTimer() <= BOMB_TIMER * 0.33)
	{
		SpriteComponent* sprite = _owner->GetComponent<SpriteComponent>();
		sprite->UpdateTexture(TEXTURE_RED_BOMB);
	}
	return nullptr;
}

void BombBehaviorComponent::blast()
{
	sDevice->PlaySound("Blast1", 0);
	oFactory->createBlast(_owner);
}
