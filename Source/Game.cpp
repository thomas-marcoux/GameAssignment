#include "Game.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

//Make Game class' attributes and initializes them
bool Game::Initialize()
{
	gDevice = std::make_unique<GraphicsDevice>();
	aLibrary = std::make_unique<ArtAssetLibrary>(gDevice.get());
	iDevice = std::make_unique<InputDevice>();
	oFactory = std::make_unique<ObjectFactory>();
	timer = std::make_unique<Timer>();
	gameTime = 0;
	view = std::make_unique<View>();
	if (gDevice->Initialize(FULLSCREEN) && iDevice->Initialize() && timer->Initialize(FPS)
		&& timer->Initialize(GAME_FPS) && view->Initialize(iDevice.get(), 0, 0))
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
	std::shared_ptr<SpriteComponent>	sprite;
	std::string name = "";

	for (auto object : objects)
	{
		sprite = object->GetComponent<SpriteComponent>();
		if (!sprite) throw LoadException(NO_COMPONENT);
		name = sprite->getName();
		if (!sprite->Initialize(gDevice.get(), aLibrary->Search(name))) throw LoadException(NO_SPRITE, name);
	}
	return true;
}

//Loads game info from both config files, catches errors occuring during loading
bool Game::LoadLevel(std::string levelConfigFile, std::string objectConfigFile)
{
	try
	{
		LoadArtAssets(objectConfigFile);
		LoadGameAssets(levelConfigFile);
		LoadSprites();
		view = std::make_unique<View>();
		view->Initialize(iDevice.get(), 0, 0);
		view->setObjects(&objects);
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
	Draw();
	timer->fpsRegulate();
	return false;
}

//Update all game actors
bool Game::Update()
{
	if (!view->Update())
		return true;
	for (auto object : objects)
		object->Update();
	return false;
}

//Draw all sprites
void Game::Draw()
{
	gDevice->Begin();
	gDevice->Draw(view.get());
	gDevice->Present();
}
