#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include "AssetLibrary.h"
#include "Definitions.h"
#include "Exceptions.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "PhysicsDevice.h"
#include "SoundDevice.h"
#include "Timer.h"
#include "View.h"

//Base game class
class Game
{
public:
	Game() : dt(1.0f / 100.0f) {}
	~Game() {}
	bool Initialize();
	void Reset();
	bool LoadResources(std::string, std::string, std::string, std::string, std::string);
	bool LoadLevel(std::string);
	bool Start(std::vector<std::string>&);
	void queueObject(std::unique_ptr<Object>);
	bool Run();
	bool Update();
	void Draw();

private:
	bool LoadAssets(std::string, std::string, std::string, std::string);
	bool LoadObjects(std::string);
	bool LoadMap(std::string const&);
	bool InitializeObjects();
	void Finish();

private:
	std::unique_ptr<AssetLibrary> aLibrary;
	std::unique_ptr<GraphicsDevice> gDevice;
	std::unique_ptr<InputDevice> iDevice;
	std::unique_ptr<ObjectFactory> oFactory;
	std::unique_ptr<PhysicsDevice> pDevice;
	std::unique_ptr<SoundDevice>	sDevice;
	std::unique_ptr<Timer> timer;
	const GAME_FLT dt; //Time per frame
	std::unique_ptr<View> view;
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<std::unique_ptr<Object>> toBeAdded;
	std::vector<int> deadObjectIDs;
};

#endif // ! GAME_H
