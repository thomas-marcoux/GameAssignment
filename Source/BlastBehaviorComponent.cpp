#include "BlastBehaviorComponent.h"

bool BlastBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const & initializers)
{
	_forceMultiplier = BLAST_FORCE;
	return true;
}

std::unique_ptr<Object> BlastBehaviorComponent::Update(GAME_FLT)
{
	_applyForce.x = (float)cosf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
	_applyForce.y = (float)sinf(TO_RADIAN(_owner->pDevice->GetAngle(_owner)) - (PI / 2))*_forceMultiplier;
	_owner->pDevice->SetLinearVelocity(_owner, _applyForce);
	return nullptr;
}
