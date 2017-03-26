#ifndef SLIDEBEHAVIORCOMPONENTFACTORY_H
#define SLIDEBEHAVIORCOMPONENTFACTORY_H

#include <memory>
#include "ComponentFactory.h"
#include "SlideBehaviorComponent.h"

class SlideBehaviorComponentFactory : public ComponentFactory
{
public:
	std::unique_ptr<Component> create(std::unique_ptr<Object>& owner) { return std::make_unique<SlideBehaviorComponent>(owner); }
};

#endif // !SLIDEBEHAVIORCOMPONENTFACTORY_H
