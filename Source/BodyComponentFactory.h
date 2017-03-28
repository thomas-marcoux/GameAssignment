#ifndef BODYCOMPONENTFACTORY_H
#define BODYCOMPONENTFACTORY_H

#include <memory>
#include "BodyComponent.h"
#include "ComponentFactory.h"

class BodyComponentFactory : public ComponentFactory
{
public:
	std::shared_ptr<Component> create(std::shared_ptr<Object> owner) { return std::make_shared<BodyComponent>(owner); }
};

#endif // !BODYCOMPONENTFACTORY_H
