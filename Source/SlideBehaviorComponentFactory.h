#ifndef SLIDEBEHAVIORCOMPONENTFACTORY_H
#define SLIDEBEHAVIORCOMPONENTFACTORY_H

#include <memory>
#include "ComponentFactory.h"
#include "SlideBehaviorComponent.h"

class SlideBehaviorComponentFactory : public ComponentFactory
{
public:
	std::shared_ptr<Component> create(std::shared_ptr<Object> owner) { return std::make_shared<SlideBehaviorComponent>(owner); }
};

#endif // !SLIDEBEHAVIORCOMPONENTFACTORY_H
