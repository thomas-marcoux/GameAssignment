#ifndef REDLEEVERFACTORY_H
#define REDLEEVERFACTORY_H

#include "ObjectFactory.h"
#include "RedLeever.h"

class RedLeeverFactory : public ObjectFactory
{
public:
	std::unique_ptr<Object> create() { return (std::unique_ptr<Object>)(std::make_unique<RedLeever>()); }
};

#endif // !REDLEEVERFACTORY_H
