#ifndef SPRITECOMPONENTFACTORY_H
#define SPRITECOMPONENTFACTORY_H

#include <memory>
#include "SpriteComponent.h"
#include "ComponentFactory.h"

class SpriteComponentFactory : public ComponentFactory
{
public:
	std::shared_ptr<Component> create(std::shared_ptr<Object> owner) { return std::make_shared<SpriteComponent>(owner); }
};

#endif // !SPRITECOMPONENTFACTORY_H
