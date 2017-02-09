#ifndef REDOCTOROKFACTORY_H
#define REDOCTOROKFACTORY_H

#include "ObjectFactory.h"
#include "RedOctorok.h"

class RedOctorokFactory : public ObjectFactory
{
public:
	std::unique_ptr<Object> create() { return (std::unique_ptr<Object>)(std::make_unique<RedOctorok>()); }
};

#endif // !REDOCTOROKFACTORY_H
