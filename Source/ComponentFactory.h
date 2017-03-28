#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "Component.h"

class ComponentFactory
{
public:
	virtual std::shared_ptr<Component> create(std::shared_ptr<Object>) = 0;
};

#endif // !COMPONENTFACTORY_H
