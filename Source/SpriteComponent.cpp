#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "GraphicsDevice.h"
#include "Object.h"

SpriteComponent::SpriteComponent(std::unique_ptr<Object> const& owner) : Component(owner)
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
	_gDevice->addSprite(this);
	if (!texture)
		return false;
	_texture = texture;
	return true;
}

void SpriteComponent::setTexture(std::shared_ptr<Texture> texture)
{
	_texture = texture;
}

bool SpriteComponent::Draw(View* p_view)
{
	BodyComponent*	body = _owner->GetComponent<BodyComponent>();

	if (!body)	return false;
	_texture->Draw(_gDevice->getRenderer(), p_view, body->getPosition(), body->getAngle());
	return true;
}
