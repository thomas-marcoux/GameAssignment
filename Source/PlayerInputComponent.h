#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "Component.h"

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(std::unique_ptr<Object>& owner) : Component(owner) {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::unique_ptr<Object> Update();
	bool Finish();
};

#endif // !PLAYERINPUTCOMPONENT_H
