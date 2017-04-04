#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "Component.h"
#include "InputDevice.h"
#include "ObjectFactory.h"

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(std::unique_ptr<Object> const&);
	~PlayerInputComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	bool Initialize(InputDevice*, ObjectFactory*);
	std::unique_ptr<Object> Update();
	bool Finish();

private:
	InputDevice* iDevice;
	ObjectFactory* oFactory;
};

#endif // !PLAYERINPUTCOMPONENT_H
