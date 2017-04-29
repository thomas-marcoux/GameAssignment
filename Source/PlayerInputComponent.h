#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "Component.h"

class InputDevice;
class ObjectFactory;
class View;

//Queries InputDevice for input, applies forces, updates textures, creates arrow
class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(std::unique_ptr<Object> const&);
	~PlayerInputComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	bool Initialize(InputDevice*, ObjectFactory*, View*);
	std::unique_ptr<Object> Update(GAME_FLT);
	bool Finish();

private:
	InputDevice* iDevice;
	ObjectFactory* oFactory;
	View*	view;
	GAME_INT _forceMultiplier;
	GAME_VEC _force;
	GAME_FLT _angle;
};

#endif // !PLAYERINPUTCOMPONENT_H
