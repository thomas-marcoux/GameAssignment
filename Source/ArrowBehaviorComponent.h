#ifndef ARROWBEHAVIORCOMPONENT_H
#define ARROWBEHAVIORCOMPONENT_H

#include "Component.h"

class ArrowBehaviorComponent : public Component
{
public:
	ArrowBehaviorComponent(std::unique_ptr<Object> const& owner) : Component(owner) {}
	~ArrowBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	std::unique_ptr<Object> Update(GAME_FLT);
	bool Finish() { return false; }

private:
	GAME_INT	_forceMultiplier;
	GAME_VEC	_applyForce;
};

#endif // !ARROWBEHAVIORCOMPONENT_H
