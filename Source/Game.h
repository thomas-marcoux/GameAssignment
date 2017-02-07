#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "ArtAssetLibrary.h"
#include "GameAssetLibrary.h"
#include "InputDevice.h"
#include "Object.h"
#include "View.h"

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
	std::unique_ptr<GameAssetLibrary> gLibrary;
	std::unique_ptr<ArtAssetLibrary> aLibrary;
	std::unique_ptr<GraphicsDevice> gDevice;
	std::unique_ptr<InputDevice> iDevice;
	std::unique_ptr<Timer> timer;
	GAME_FLT gameTime;
	std::unique_ptr<View> view;
	std::vector<std::unique_ptr<Object>> objects;
}

#endif // ! GAME_H
