#ifndef CIRCLEBEHAVIORCOMPONENTFACTORY_H
#define CIRCLEBEHAVIORCOMPONENTFACTORY_H

#include <memory>
#include "ComponentFactory.h"
#include "CircleBehaviorComponent.h"

class CircleBehaviorComponentFactory : public ComponentFactory
{
public:
	std::shared_ptr<Component> create(std::shared_ptr<Object> owner) { return std::make_shared<CircleBehaviorComponent>(owner);  }
};

#endif // !CIRCLEBEHAVIORCOMPONENTFACTORY_H
