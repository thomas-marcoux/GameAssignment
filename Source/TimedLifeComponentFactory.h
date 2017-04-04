#ifndef TIMEDLIFECOMPONENTFACTORY_H
#define TIMEDLIFECOMPONENTFACTORY_H

#include <memory>
#include "TimedLifeComponent.h"
#include "ComponentFactory.h"

class TimedLifeComponentFactory : public ComponentFactory
{
public:
	std::unique_ptr<Component> create(std::unique_ptr<Object> const& owner) { return std::make_unique<TimedLifeComponent>(owner); }
};


#endif // !TIMEDLIFECOMPONENTFACTORY_H
