#ifndef CIRCLEBEHAVIORCOMPONENTFACTORY_H
#define CIRCLEBEHAVIORCOMPONENTFACTORY_H

#include <memory>
#include "ComponentFactory.h"
#include "CircleBehaviorComponent.h"

class CircleBehaviorComponentFactory : public ComponentFactory
{
public:
	std::unique_ptr<Component> create(std::unique_ptr<Object> const& owner) { return std::make_unique<CircleBehaviorComponent>(owner);  }
};

#endif // !CIRCLEBEHAVIORCOMPONENTFACTORY_H
