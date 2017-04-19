#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include "Texture.h"

class GraphicsDevice;

//Manages Object display
class SpriteComponent : public Component
{
public:
	SpriteComponent(std::unique_ptr<Object> const&);
	~SpriteComponent();
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	bool Initialize(GraphicsDevice*, std::shared_ptr<Texture>);
	std::unique_ptr<Object> Update(GAME_FLT) { return NULL; }
	bool Finish();
	bool Draw(View*);
	std::string getName() { return _name; }
	GraphicsDevice* getGDevice() { return _gDevice; }
	std::shared_ptr<Texture> getTexture() { return _texture; }
	bool LoadTexture(TEXTURE_ID, std::shared_ptr<Texture>);
	void UpdateTexture();

private:
	std::string	_name;
	std::shared_ptr<Texture> _texture;
	std::vector<std::shared_ptr<Texture>>	_textures;
	GraphicsDevice* _gDevice;
};

#endif // !SPRITECOMPONENT_H
