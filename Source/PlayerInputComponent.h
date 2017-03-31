#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "Component.h"
#include "InputDevice.h"

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(std::shared_ptr<Object> owner) : Component(owner) {}
	~PlayerInputComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	bool Initialize(InputDevice*);
	bool LoadTexture(TEXTURE_ID, std::shared_ptr<Texture>);
	std::unique_ptr<Object> Update();
	void UpdateTexture();
	bool Finish();

private:
	std::unique_ptr<Object> CreateArrow();

private:
	InputDevice* iDevice;
	std::vector<std::shared_ptr<Texture>>	_textures;
};

#endif // !PLAYERINPUTCOMPONENT_H
