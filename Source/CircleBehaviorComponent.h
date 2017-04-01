#ifndef CIRCLEBEHAVIORCOMPONENT_H
#define CIRCLEBEHAVIORCOMPONENT_H

#include "Component.h"

class CircleBehaviorComponent : public Component
{
public:
	CircleBehaviorComponent(std::unique_ptr<Object> const& owner) : Component(owner) {}
	~CircleBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::unique_ptr<Object> Update();
	bool Finish();

private:
	GAME_FLT _radius;
	GAME_FLT _movement;
	GAME_FLT _movementAngle;
};

#endif // !CIRCLEBEHAVIORCOMPONENT_H
