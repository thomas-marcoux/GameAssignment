#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "Component.h"

class InputDevice;
class ObjectFactory;
class View;

//Queries InputDevice for input, updates the Object's other components
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
};

#endif // !PLAYERINPUTCOMPONENT_H
