#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include "Texture.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(std::shared_ptr<Object>);
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	bool Initialize(GraphicsDevice*, std::shared_ptr<Texture>);
	std::unique_ptr<Object> Update() { return NULL; }
	bool Finish();
	bool Draw(View*);
	std::string getName() { return _name; }

private:
	std::string	_name;
	std::shared_ptr<Texture> _texture;
	GraphicsDevice* _gDevice;
};

#endif // !SPRITECOMPONENT_H
