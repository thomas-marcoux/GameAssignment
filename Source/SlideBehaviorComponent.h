#ifndef SLIDEBEHAVIORCOMPONENT_H
#define SLIDEBEHAVIORCOMPONENT_H

#include "Component.h"

//Updates Leever Objects' BodyComponent by sliding horizontally or vertically
class SlideBehaviorComponent : public Component
{
public:
	SlideBehaviorComponent(std::unique_ptr<Object> const& owner) : Component(owner) {}
	~SlideBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	std::unique_ptr<Object> Update(GAME_FLT);
	bool Finish() { return false; }

private:
	bool		_vertical;
	GAME_FLT	_movement;
	GAME_FLT	_maxDistance;
};
#endif // !SLIDEBEHAVIORCOMPONENT_H
