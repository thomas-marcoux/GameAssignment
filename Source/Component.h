#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include "Definitions.h"
#include "Exceptions.h"
#include "Object.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

class Component
{
public:
	Component(std::shared_ptr<Object> owner) : _owner(owner) {}
	virtual bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers) = 0;
	virtual std::shared_ptr<Object> Update() = 0;
	virtual bool Finish() = 0;

protected:
	std::shared_ptr<Object>	_owner;
};

#endif // !COMPONENT_H
