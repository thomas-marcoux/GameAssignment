#ifndef ARROWBEHAVIORCOMPONENT_H
#define ARROWBEHAVIORCOMPONENT_H

#include "Component.h"

class ArrowBehaviorComponent : public Component
{
public:
	ArrowBehaviorComponent(std::unique_ptr<Object> const& owner) : Component(owner) {}
	~ArrowBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	std::unique_ptr<Object> Update();
	bool Finish() { return false; }

private:
	GAME_FLT _movement;
	GAME_FLT _movementAngle;
};

#endif // !ARROWBEHAVIORCOMPONENT_H
