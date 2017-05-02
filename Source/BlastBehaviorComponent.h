#ifndef BLASTBEHAVIORCOMPONENT_H
#define BLASTBEHAVIORCOMPONENT_H

#include "Component.h"

class BlastBehaviorComponent : public Component
{
public:
	BlastBehaviorComponent(std::unique_ptr<Object> const& owner) : Component(owner) {}
	~BlastBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	std::unique_ptr<Object> Update(GAME_FLT);
	bool Finish() { return false; }

private:
	GAME_INT	_forceMultiplier;
	GAME_VEC	_applyForce;
};

#endif // !BLASTBEHAVIORCOMPONENT_H
