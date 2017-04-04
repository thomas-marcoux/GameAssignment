#ifndef ARROWBEHAVIORCOMPONENTFACTORY_H
#define ARROWBEHAVIORCOMPONENTFACTORY_H

#include <memory>
#include "ComponentFactory.h"
#include "ArrowBehaviorComponent.h"

class ArrowBehaviorComponentFactory : public ComponentFactory
{
public:
	std::unique_ptr<Component> create(std::unique_ptr<Object> const& owner) { return std::make_unique<ArrowBehaviorComponent>(owner); }
};

#endif // !ARROWBEHAVIORCOMPONENTFACTORY_H
