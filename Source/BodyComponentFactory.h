#ifndef BODYCOMPONENTFACTORY_H
#define BODYCOMPONENTFACTORY_H

#include <memory>
#include "BodyComponent.h"
#include "ComponentFactory.h"

class BodyComponentFactory : public ComponentFactory
{
public:
	std::unique_ptr<Component> create(std::unique_ptr<Object>& owner) { return std::make_unique<BodyComponent>(owner); }
};

#endif // !BODYCOMPONENTFACTORY_H
