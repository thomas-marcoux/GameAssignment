#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <memory>
#include "Object.h"

class ObjectFactory
{
public:
	virtual std::unique_ptr<Object> create() = 0;
};

#endif // !OBJECTFACTORY_H
