#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(std::unique_ptr<Object>& owner) : Component(owner)
{
	_name = "";
	_gDevice = NULL;
	_texture = NULL;
}

bool SpriteComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	_name = initializers.name;
	return true;
}

bool SpriteComponent::Finish()
{
	return false;
}

bool SpriteComponent::Initialize(GraphicsDevice* gDevice, std::shared_ptr<Texture> texture)
{
	_gDevice = gDevice;
	_texture = texture;
	_gDevice->AddSprite(this);
	return true;
}

bool SpriteComponent::Draw(View* p_view)
{
	_texture->Draw(_gDevice->getRenderer(), p_view, position, angle);
	return true;
}
