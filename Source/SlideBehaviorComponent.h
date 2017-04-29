#ifndef SLIDEBEHAVIORCOMPONENT_H
#define SLIDEBEHAVIORCOMPONENT_H

#include "Component.h"

//Apply forces to the Object's physics body
class SlideBehaviorComponent : public Component
{
public:
	SlideBehaviorComponent(std::unique_ptr<Object> const& owner) : Component(owner) {}
	~SlideBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	std::unique_ptr<Object> Update(GAME_FLT);
	void turn();
	void checkDistance();
	bool Finish() { return false; }

private:
	bool		_vertical;
	GAME_VEC	_startPosition;
	GAME_FLT	_maxDistance;
	GAME_INT	_forceMultiplier;
	GAME_VEC	_applyForce;
	bool		_forward; //Controls direction
};
#endif // !SLIDEBEHAVIORCOMPONENT_H
