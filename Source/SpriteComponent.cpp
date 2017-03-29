#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "GraphicsDevice.h"
#include "Object.h"

SpriteComponent::SpriteComponent(std::shared_ptr<Object> owner) : Component(owner)
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
	if (!texture)
		return false;
	_gDevice = gDevice;
	_texture = texture;
	_gDevice->addSprite(this);
	return true;
}

bool SpriteComponent::Draw(View* p_view)
{
	std::shared_ptr<BodyComponent>	body = _owner->GetComponent<BodyComponent>();

	if (!body)	return false;
	_texture->Draw(_gDevice->getRenderer(), p_view, body->getPosition(), body->getAngle());
	return true;
}
