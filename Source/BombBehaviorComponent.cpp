#include "BombBehaviorComponent.h"
#include <iostream>

bool BombBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const & initializers)
{
	return true;
}

std::unique_ptr<Object> BombBehaviorComponent::Update(GAME_FLT)
{
	return nullptr;
}

void BombBehaviorComponent::blast()
{
	std::cout << "boom\n";
}
