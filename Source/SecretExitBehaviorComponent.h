#ifndef SECRETEXITBEHAVIORCOMPONENT_H
#define SECRETEXITBEHAVIORCOMPONENT_H

#include "Component.h"

class SecretExitBehaviorComponent : public Component
{
public:
	SecretExitBehaviorComponent(std::unique_ptr<Object> const& owner) : Component(owner) {}
	~SecretExitBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	std::unique_ptr<Object> Update(GAME_FLT);
	bool Finish() { return false; }
};

#endif // !SECRETEXITBEHAVIORCOMPONENT_H
