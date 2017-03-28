#ifndef SLIDEBEHAVIORCOMPONENT_H
#define SLIDEBEHAVIORCOMPONENT_H

#include "Component.h"

class SlideBehaviorComponent : public Component
{
public:
	SlideBehaviorComponent(std::shared_ptr<Object> owner) : Component(owner) {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::unique_ptr<Object> Update();
	bool Finish() { return false; }

private:
	bool		_vertical;
	GAME_FLT	_movement;
	GAME_FLT	_maxDistance;
};
#endif // !SLIDEBEHAVIORCOMPONENT_H
