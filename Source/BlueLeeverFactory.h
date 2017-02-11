#ifndef BLUELEEVERFACTORY_H
#define BLUELEEVERFACTORY_H

#include "ObjectFactory.h"
#include "BlueLeever.h"

class BlueLeeverFactory : public ObjectFactory
{
public:
	std::unique_ptr<Object> create() { return std::make_unique<BlueLeever>(); }
};

#endif // !BLUELEEVERFACTORY_H
