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
	std::unique_ptr<Object> Update();
	bool Finish();

private:
	InputDevice* iDevice;
	ObjectFactory* oFactory;
	View*	view;
};

#endif // !PLAYERINPUTCOMPONENT_H
