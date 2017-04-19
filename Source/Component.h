#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include "Definitions.h"
#include "Object.h"
#include "PhysicsDevice.h"

//Base Component class
class Component
{
public:
	Component(std::unique_ptr<Object> const&);
	virtual ~Component() {}
	virtual bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers) = 0;
	virtual std::unique_ptr<Object> Update() = 0;
	virtual bool Finish() = 0;

protected:
	Object*	_owner;
};

#endif // !COMPONENT_H
