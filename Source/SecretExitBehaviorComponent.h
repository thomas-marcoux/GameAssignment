#ifndef SECRETEXITBEHAVIORCOMPONENT_H
#define SECRETEXITBEHAVIORCOMPONENT_H

#include "Component.h"

class ObjectFactory;

class SecretExitBehaviorComponent : public Component
{
public:
	SecretExitBehaviorComponent(std::unique_ptr<Object> const& owner) : Component(owner) {}
	~SecretExitBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	bool Initialize(ObjectFactory*);
	std::unique_ptr<Object> Update(GAME_FLT);
	bool Finish() { return false; }

private:
	ObjectFactory*	oFactory;
};

#endif // !SECRETEXITBEHAVIORCOMPONENT_H
