#include "SpriteComponent.h"
#include "GraphicsDevice.h"
#include "Object.h"

SpriteComponent::SpriteComponent(std::unique_ptr<Object> const& owner) : Component(owner)
{
	_name = "";
	_gDevice = NULL;
	_texture = NULL;
	_textures.assign(NB_TEXTURES, nullptr);
}

SpriteComponent::~SpriteComponent()
{
	_gDevice->removeSprite(this);
}

bool SpriteComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers)
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

//Add texture to a vector for objects facing different directions
bool SpriteComponent::LoadTexture(TEXTURE_ID id, std::shared_ptr<Texture> texture)
{
	_textures[id] = texture;
	return false;
}

//Update the active texture depending on what direction the object is facing
void SpriteComponent::UpdateTexture(TEXTURE_ID id)
{
	_texture = _textures[id];
}

bool SpriteComponent::Draw(View* p_view)
{
	_texture->Draw(_gDevice->getRenderer(), p_view, _owner->pDevice->GetPosition(_owner), _owner->pDevice->GetAngle(_owner));
	return true;
}
