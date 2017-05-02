#include <algorithm>
#include <fstream>
#include <sstream>
#include "Game.h"
#include "CircleBehaviorComponent.h"
#include "SpriteComponent.h"
#include "PlayerInputComponent.h"
#include "SecretExitBehaviorComponent.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

//Make Game class' attributes and initializes them
bool Game::Initialize()
{
	GAME_VEC gravity;
	gravity.x = 0.0f;
	gravity.y = 0.0f;
	gDevice = std::make_unique<GraphicsDevice>();
	sDevice = std::make_unique<SoundDevice>();
	aLibrary = std::make_unique<AssetLibrary>(gDevice.get(), sDevice.get());
	iDevice = std::make_unique<InputDevice>();
	oFactory = std::make_unique<ObjectFactory>();
	pDevice = std::make_unique<PhysicsDevice>(gravity);
	timer = std::make_unique<Timer>();
	view = std::make_unique<View>();
	if (gDevice->Initialize(FULLSCREEN) && iDevice->Initialize() && timer->Initialize(FPS) && pDevice->Initialize()
		&& sDevice->Initialize(aLibrary) && timer->Initialize(GAME_FPS) && view->Initialize(iDevice.get(), 0, 0)
		&& oFactory->Initialize(this, aLibrary, gDevice, pDevice, sDevice))
		return true;
	return false;
}

//Reset view and objects
void Game::Reset()
{
	view.reset(NULL);
	objects.clear();
}

//Load object file and add assets from attributes. Raises LoadException if an error occurs.
bool Game::LoadAssets(std::string objectConfigFile, std::string physicsConfigFile, std::string soundEffectsFile, std::string musicFile)
{
	if (!aLibrary->LoadArt(objectConfigFile) || !aLibrary->LoadPhysics(physicsConfigFile) || !aLibrary->LoadSoundEffects(soundEffectsFile)
		|| !aLibrary->LoadMusic(musicFile))
		return false;
	return true;
}

bool Game::LoadObjects(std::string objectConfigFile)
{
	TiXmlDocument doc;
	TiXmlElement* gameAssetNode;

	if (!doc.LoadFile(objectConfigFile.c_str())) throw LoadException(LOAD_ERROR, objectConfigFile);
	gameAssetNode = TiXmlHandle(doc.RootElement()).FirstChild("GameAsset").Element();
	if (!gameAssetNode) throw LoadException(PARSE_ERROR, objectConfigFile);
	//Goes through every game asset node and sends them to the object factory which returns an object
	for (gameAssetNode; gameAssetNode; gameAssetNode = gameAssetNode->NextSiblingElement())
		aLibrary->LoadObject(gameAssetNode);
	return true;
}

bool Game::LoadMap(std::string const& mapFile)
{
	std::unique_ptr<Object> new_object = nullptr;
	GAME_VEC	increment = { SPRITE_WIDTH, SPRITE_HEIGHT };
	GAME_VEC	start = { 50, 50 };
	GAME_VEC	coord = { 0, start.y };
	std::ifstream file;
	std::string	line;

	file.open(mapFile);
	if (!file.is_open())
		throw LoadException(LOAD_ERROR, mapFile);
	while (std::getline(file, line))
	{
		coord.x = start.x;
		for (GAME_INT i = 0; i < line.size(); i++)
		{
			new_object = oFactory->create(line.substr(i, 1), coord);
			if (new_object)
				objects.push_back(std::move(new_object));
			coord.x += increment.x;
		}
		coord.y += increment.y;
	}
	file.close();
	return true;
}

bool Game::InitializeObjects()
{
	for (auto const& object : objects)
	{
		SpriteComponent* sprite;
		switch (object->getType())
		{
		case (PLAYER_TYPE):
			sprite = object->GetComponent<SpriteComponent>();
			object->GetComponent<PlayerInputComponent>()->Initialize(iDevice.get(), oFactory.get(), view.get());
			sprite->LoadTexture(TEXTURE_UP, aLibrary->SearchArt("Player Up"));
			sprite->LoadTexture(TEXTURE_DOWN, aLibrary->SearchArt("Player Down"));
			sprite->LoadTexture(TEXTURE_LEFT, aLibrary->SearchArt("Player Left"));
			sprite->LoadTexture(TEXTURE_RIGHT, aLibrary->SearchArt("Player Right"));
			sprite->UpdateTexture(TEXTURE_UP);
			break;
		case (OCTOROK_TYPE):
			object->GetComponent<CircleBehaviorComponent>()->Initialize(oFactory.get());
			break;
		case (SECRET_EXIT_TYPE):
			object->GetComponent<SecretExitBehaviorComponent>()->Initialize(oFactory.get());
			break;
		default:
			break;
		}
	}
	return true;
}


bool Game::LoadResources(std::string objectConfigFile, std::string physicsConfigFile, std::string spritesConfigFile,
	std::string soundConfigFile, std::string musicConfigFile)
{
	try
	{
		view = std::make_unique<View>();
		view->Initialize(iDevice.get(), 0, 0);
		LoadAssets(spritesConfigFile, physicsConfigFile, "./Assets/Config/sounds.xml", "./Assets/Config/music.xml");
		LoadObjects(objectConfigFile);
		std::cout << "Resources Loaded." << std::endl;
		return true;
	}
	catch (LoadException &e)
	{
		std::cout << e.getMsg().c_str() << std::endl;
		system("PAUSE");
		return false;
	}
}

//Loads game info from both config files, catches errors occuring during loading
bool Game::LoadLevel(std::string levelConfigFile)
{
	try
	{
		LoadMap(levelConfigFile);
		InitializeObjects();
		sDevice->PlayMusic("Music1");
		std::cout << "Game Loaded." << std::endl;
		return true;
	}
	catch (LoadException &e)
	{
		std::cout << e.getMsg().c_str() << std::endl;
		system("PAUSE");
		return false;
	}
}

bool Game::Start(std::vector<std::string>& levels)
{
	while (!levels.empty())
	{
		if (!LoadLevel(levels.back()))
			return false;
		levels.pop_back();
	}
	return true;
}

void Game::queueObject(std::unique_ptr<Object> object)
{
	toBeAdded.push_back(std::move(object));
}

//Runs one game frame and regulate the fps
bool Game::Run()
{
	timer->start();
	if (Update())
		return true;
	Finish();
	Draw();
	timer->fpsRegulate();
	return false;
}

//Update all game actors
bool Game::Update()
{
	std::unique_ptr<Object> new_object = nullptr;
	int id = 0;

	if (!view->Update())
		return true;
	for (auto object = objects.begin(); object != objects.end(); object++, id++)
	{
		std::string name = (*object)->getName();
		new_object = std::move((*object)->Update(dt));
		if ((*object)->isDead()) //If object is dead, store its ID to be deleted
			deadObjectIDs.push_back(id);
		if (new_object)
			queueObject(std::move(new_object));
	}
	pDevice->Update(dt);
	return false;
}

//Delete dead objects, calls PhysicsDevice's RemoveObject and resets the parent's child pointer
void Game::Finish()
{
	while (deadObjectIDs.size() > 0)
	{
		GAME_INT id = deadObjectIDs.back();
		Object* object = objects[id].get();
		Object* parent = object->getParent();
		if (parent != nullptr)
			parent->setChild(nullptr);
		object->pDevice->RemoveObject(object);
		objects.erase(objects.begin() + id);
		deadObjectIDs.pop_back();
	}
	while (toBeAdded.size() > 0)
	{
		objects.push_back(std::move(toBeAdded.back()));
		toBeAdded.pop_back();
	}
}

//Draw all sprites
void Game::Draw()
{
	gDevice->Begin();
	gDevice->Draw(view.get());
	gDevice->Present();
}
