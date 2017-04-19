#include <algorithm>
#include "Game.h"
#include "SpriteComponent.h"
#include "PlayerInputComponent.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

//Make Game class' attributes and initializes them
bool Game::Initialize()
{
	GAME_VEC gravity;
	gravity.x = 0;
	gravity.y = 0;
	gDevice = std::make_unique<GraphicsDevice>();
	aLibrary = std::make_unique<AssetLibrary>(gDevice.get());
	iDevice = std::make_unique<InputDevice>();
	oFactory = std::make_unique<ObjectFactory>();
	pDevice = std::make_unique<PhysicsDevice>(gravity);
	timer = std::make_unique<Timer>();
	gameTime = 0;
	view = std::make_unique<View>();
	if (gDevice->Initialize(FULLSCREEN) && iDevice->Initialize() && timer->Initialize(FPS) && pDevice->Initialize()
		&& timer->Initialize(GAME_FPS) && view->Initialize(iDevice.get(), 0, 0) && oFactory->Initialize(aLibrary, pDevice))
		return true;
	return false;
}

//Reset view and objects
void Game::Reset()
{
	view.reset(NULL);
	objects.clear();
}

//Load level file and create objects from attributes. Raises LoadException if an error occurs.
bool Game::LoadGameAssets(std::string levelConfigFile)
{
	TiXmlDocument doc;
	TiXmlElement* gameAssetNode;

	if (!doc.LoadFile(levelConfigFile.c_str())) throw LoadException(LOAD_ERROR, levelConfigFile);
	gameAssetNode = TiXmlHandle(doc.RootElement()).FirstChild("GameAsset").Element();
	if (!gameAssetNode) throw LoadException(PARSE_ERROR, levelConfigFile);
	//Goes through every game asset node and sends them to the object factory which returns an object
	for (gameAssetNode; gameAssetNode; gameAssetNode = gameAssetNode->NextSiblingElement())
		objects.push_back(oFactory->create(gameAssetNode));		
	return true;
}

//Load object file and add assets from attributes. Raises LoadException if an error occurs.
bool Game::LoadArtAssets(std::string objectConfigFile)
{
	TiXmlDocument doc;
	TiXmlElement* itemNode;
	const char *attr_name, *attr_path;

	//Tries to open the level configFile, raises an error if it cannot
	if (!doc.LoadFile(objectConfigFile.c_str())) throw LoadException(LOAD_ERROR, objectConfigFile);
	itemNode = TiXmlHandle(doc.RootElement()).FirstChild("Item").Element();
	if (!itemNode) throw LoadException(PARSE_ERROR, objectConfigFile);
	for (itemNode; itemNode; itemNode = itemNode->NextSiblingElement())
	{
		attr_name = itemNode->Attribute("name");
		attr_path = itemNode->Attribute("sprite");
		if (!attr_name || !attr_path) throw LoadException(PARSE_ERROR, objectConfigFile); //Checks attributes exist
		aLibrary->AddAsset(attr_name, attr_path);
	}
	return true;
}

//Loads Textures and GraphicsDevice into the Sprite components, throws error for missing sprites
bool Game::LoadSprites()
{
	SpriteComponent *sprite;
	std::string name = "";

	for (auto const& object : objects)
	{
		sprite = object->GetComponent<SpriteComponent>();
		if (!sprite) throw LoadException(NO_COMPONENT);
		name = sprite->getName();
		sprite->Initialize(gDevice.get(), aLibrary->Search(name));
		if (name == "Link")
		{
			sprite->LoadTexture(TEXTURE_UP, aLibrary->Search("Link Up"));
			sprite->LoadTexture(TEXTURE_DOWN, aLibrary->Search("Link Down"));
			sprite->LoadTexture(TEXTURE_LEFT, aLibrary->Search("Link Left"));
			sprite->LoadTexture(TEXTURE_RIGHT, aLibrary->Search("Link Right"));
			sprite->UpdateTexture();
		}	
	}
	return true;
}

//Loads PlayerInputComponent
bool Game::LoadPlayer()
{
	PlayerInputComponent *player;
	for (auto const& object : objects)
	{
		player = object->GetComponent<PlayerInputComponent>();
		if (player)
			player->Initialize(iDevice.get(), oFactory.get(), view.get());
	}
	return true;
}

bool Game::LoadPhysics()
{
	for (auto const& object : objects)
		oFactory->loadPhysics(object);
	return true;
}

//Loads game info from both config files, catches errors occuring during loading
bool Game::LoadLevel(std::string levelConfigFile, std::string objectConfigFile)
{
	try
	{
		view = std::make_unique<View>();
		view->Initialize(iDevice.get(), 0, 0);
		LoadArtAssets(objectConfigFile);
		LoadGameAssets(levelConfigFile);
		LoadSprites();
		LoadPlayer();
		LoadPhysics();
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
	std::unique_ptr<Object>	r;
	GAME_FLT time = timer->getTime();
	int id = 0;

	if (!view->Update())
		return true;
	for (auto object = objects.begin(); object != objects.end(); object++, id++)
	{
		r = std::move((*object)->Update(time));
		if ((*object)->isDead()) //If object is dead, store its ID to be deleted
			deadObjectIDs.push_back(id);
		if (r)
			new_object = std::move(r);
	}
	pDevice->Update(time);
	if (new_object) //If a new object has been created, add it to the vector
		objects.push_back(std::move(new_object));
	return false;
}

//Delete dead objects
void Game::Finish()
{
	while (deadObjectIDs.size() > 0)
	{
		objects.erase(objects.begin() + deadObjectIDs.back());
		deadObjectIDs.pop_back();
	}
}

//Draw all sprites
void Game::Draw()
{
	gDevice->Begin();
	gDevice->Draw(view.get());
	gDevice->Present();
}
