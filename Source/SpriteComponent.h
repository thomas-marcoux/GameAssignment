#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include "Texture.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(std::unique_ptr<Object>& owner) : Component(owner) {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::unique_ptr<Object> Update();
	bool Finish();
	bool addTexture(std::shared_ptr<Texture>);
	bool Draw(View*);

private:
	std::shared_ptr<Texture> texture;
};

#endif // !SPRITECOMPONENT_H
