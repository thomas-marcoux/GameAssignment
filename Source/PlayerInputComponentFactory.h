#ifndef PLAYERINPUTCOMPONENTFACTORY_H
#define PLAYERINPUTCOMPONENTFACTORY_H

#include <memory>
#include "ComponentFactory.h"
#include "PlayerInputComponent.h"

class PlayerInputComponentFactory : public ComponentFactory
{
public:
	std::unique_ptr<Component> create(std::unique_ptr<Object> const& owner) { return std::make_unique<PlayerInputComponent>(owner); }
};

#endif // !PLAYERINPUTCOMPONENTFACTORY_H
