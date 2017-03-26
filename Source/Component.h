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
	Component(std::unique_ptr<Object>& owner) : _owner(owner.get()) {}
	virtual bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers) = 0;
	virtual std::unique_ptr<Object> Update() = 0;
	virtual bool Finish() = 0;

protected:
	std::unique_ptr<Object>	_owner;
};

#endif // !COMPONENT_H
