#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "ArtAssetLibrary.h"
#include "Definitions.h"
#include "Exceptions.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "SpriteComponent.h"
#include "Timer.h"
#include "View.h"

//Base game class
class Game
{
public:
	Game() {}
	~Game() {}
	bool Initialize();
	void Reset();
	bool LoadLevel(std::string, std::string);
	bool Run();
	bool Update();
	void Draw();

private:
	bool LoadGameAssets(std::string);
	bool LoadArtAssets(std::string);
	bool LoadSprites();

private:
	std::unique_ptr<ArtAssetLibrary> aLibrary;
	std::unique_ptr<GraphicsDevice> gDevice;
	std::unique_ptr<InputDevice> iDevice;
	std::unique_ptr<ObjectFactory> oFactory;
	std::unique_ptr<Timer> timer;
	GAME_FLT gameTime;
	std::unique_ptr<View> view;
	std::vector<std::shared_ptr<Object>> objects;
};

#endif // ! GAME_H
