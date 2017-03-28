#ifndef PLAYERINPUTCOMPONENTFACTORY_H
#define PLAYERINPUTCOMPONENTFACTORY_H

#include <memory>
#include "ComponentFactory.h"
#include "PlayerInputComponent.h"

class PlayerInputComponentFactory : public ComponentFactory
{
public:
	std::shared_ptr<Component> create(std::shared_ptr<Object> owner) { return std::make_unique<PlayerInputComponent>(owner); }
};

#endif // !PLAYERINPUTCOMPONENTFACTORY_H
