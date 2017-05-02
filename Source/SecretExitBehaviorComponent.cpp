#include "SecretExitBehaviorComponent.h"
#include "ObjectFactory.h"

bool SecretExitBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const & initializers)
{
	return true;
}

bool SecretExitBehaviorComponent::Initialize(ObjectFactory* oF)
{
	oFactory = oF;
	return true;
}

std::unique_ptr<Object> SecretExitBehaviorComponent::Update(GAME_FLT)
{
	if (_owner->isDead())
	{
		GAME_VEC	exit_pos = _owner->pDevice->GetPosition(_owner);
		exit_pos.x += SPRITE_WIDTH_2;
		exit_pos.y += SPRITE_HEIGHT_2;
		return oFactory->create("e", exit_pos);
	}
	return nullptr;
}
