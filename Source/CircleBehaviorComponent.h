#ifndef CIRCLEBEHAVIORCOMPONENT_H
#define CIRCLEBEHAVIORCOMPONENT_H

#include "Component.h"

class CircleBehaviorComponent : public Component
{
public:
	CircleBehaviorComponent(std::shared_ptr<Object> owner) : Component(owner) {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::shared_ptr<Object> Update();
	bool Finish();

private:
	GAME_FLT _radius;
	GAME_FLT _movementAngle;
};

#endif // !CIRCLEBEHAVIORCOMPONENT_H
