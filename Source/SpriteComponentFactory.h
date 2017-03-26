#ifndef SPRITECOMPONENTFACTORY_H
#define SPRITECOMPONENTFACTORY_H

#include <memory>
#include "SpriteComponent.h"
#include "ComponentFactory.h"

class SpriteComponentFactory : public ComponentFactory
{
public:
	std::unique_ptr<Component> create(std::unique_ptr<Object>& owner) { return std::make_unique<SpriteComponent>(owner); }
};

#endif // !SPRITECOMPONENTFACTORY_H
