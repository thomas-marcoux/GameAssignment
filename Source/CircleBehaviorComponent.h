#ifndef CIRCLEBEHAVIORCOMPONENT_H
#define CIRCLEBEHAVIORCOMPONENT_H

#include "Component.h"
#include "ObjectFactory.h"

//Apply forces to the Object's physics body
class CircleBehaviorComponent : public Component
{
public:
	CircleBehaviorComponent(std::unique_ptr<Object> const& owner) : Component(owner) {}
	~CircleBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	bool Initialize(ObjectFactory*);
	std::unique_ptr<Object> Update(GAME_FLT);
	bool Finish();

private:
	GAME_FLT _radius;
	GAME_INT _forceMultiplier;
	GAME_VEC _applyForce;
	std::unique_ptr<Object> _anchor;
	std::unique_ptr<Object> _lever;
};

#endif // !CIRCLEBEHAVIORCOMPONENT_H
