#ifndef BODYCOMPONENT_H
#define BODYCOMPONENT_H

#include "Component.h"

class BodyComponent : public Component
{
public:
	BodyComponent(std::unique_ptr<Object>& owner) : Component(owner) {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::unique_ptr<Object> Update() {}
	bool Finish() { return false; }

private:
	GAME_VEC _position;
	GAME_VEC _startPosition;
	GAME_FLT _angle;
	GAME_FLT _movement;
};

#endif // !BODYCOMPONENT_H
