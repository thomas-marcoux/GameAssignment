#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "Component.h"
#include "ArrowFactory.h"
#include "InputDevice.h"

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(std::unique_ptr<Object> const&);
	~PlayerInputComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	bool Initialize(InputDevice*);
	bool LoadTexture(TEXTURE_ID, std::shared_ptr<Texture>);
	std::unique_ptr<Object> Update();
	void UpdateTexture();
	bool Finish();

private:
	InputDevice* iDevice;
	std::vector<std::shared_ptr<Texture>>	_textures;
	std::unique_ptr<ArrowFactory> arrowFactory;
};

#endif // !PLAYERINPUTCOMPONENT_H
