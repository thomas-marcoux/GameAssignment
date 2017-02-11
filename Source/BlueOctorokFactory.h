#ifndef BLUEOCTOROKFACTORY_H
#define BLUEOCTOROKFACTORY_H

#include "ObjectFactory.h"
#include "BlueOctorok.h"

class BlueOctorokFactory : public ObjectFactory
{
public:
	std::unique_ptr<Object> create() { return std::make_unique<BlueOctorok>(); }
};

#endif // !BLUEOCTOROKFACTORY_H
