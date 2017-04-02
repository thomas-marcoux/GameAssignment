#ifndef ARROWFACTORY_H
#define ARROWFACTORY_H

#include "Object.h"

class ArrowFactory
{
public:
	std::unique_ptr<Object> create(Object*, std::shared_ptr<Texture>);
};

#endif // !ARROWFACTORY_H
