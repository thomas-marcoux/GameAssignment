#ifndef CIRCLEBEHAVIORCOMPONENT_H
#define CIRCLEBEHAVIORCOMPONENT_H

#include "Component.h"

//Updates Octorok Objects's BodyComponent by circling around a point or on itself
class CircleBehaviorComponent : public Component
{
public:
	CircleBehaviorComponent(std::unique_ptr<Object> const& owner) : Component(owner) {}
	~CircleBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	std::unique_ptr<Object> Update(GAME_FLT);
	bool Finish();

private:
	GAME_FLT _radius;
	GAME_FLT _movement;
	GAME_FLT _movementAngle;
};

#endif // !CIRCLEBEHAVIORCOMPONENT_H
