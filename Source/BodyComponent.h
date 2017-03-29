#ifndef BODYCOMPONENT_H
#define BODYCOMPONENT_H

#include "Component.h"

class BodyComponent : public Component
{
public:
	BodyComponent(std::shared_ptr<Object>);
	~BodyComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::unique_ptr<Object> Update() { return NULL; }
	bool Finish() { return false; }
	GAME_VEC	getPosition() { return _position; }
	GAME_VEC	getStartPosition() { return _startPosition; }
	GAME_FLT	getAngle() { return _angle; }
	void setPosition(GAME_VEC pos) { _position = pos; }
	void setAngle(GAME_FLT angle) { _angle = angle; }

private:
	GAME_VEC _position;
	GAME_VEC _startPosition;
	GAME_FLT _angle;
};

#endif // !BODYCOMPONENT_H
