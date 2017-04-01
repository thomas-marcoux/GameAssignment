#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "Component.h"

class ComponentFactory
{
public:
	virtual std::unique_ptr<Component> create(std::unique_ptr<Object> const&) = 0;
};

#endif // !COMPONENTFACTORY_H
