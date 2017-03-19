#include "Game.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

//Make Game class' attributes and initializes them
bool Game::Initialize()
{
	gLibrary = std::make_unique<GameAssetLibrary>();
	gDevice = std::make_unique<GraphicsDevice>();
	aLibrary = std::make_unique<ArtAssetLibrary>(gDevice.get());
	iDevice = std::make_unique<InputDevice>();
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
	const char	*name;
	GAME_VEC	vec;
	GAME_FLT	angle;
	std::shared_ptr<Texture>	texture;
	std::unique_ptr<Object>		object;

	if (!doc.LoadFile(levelConfigFile.c_str())) throw LoadException(LOAD_ERROR);
	gameAssetNode = TiXmlHandle(doc.RootElement()).FirstChild("GameAsset").Element();
	if (!gameAssetNode) throw LoadException(PARSE_ERROR);
	//Goes through every game asset node
	for (gameAssetNode; gameAssetNode; gameAssetNode = gameAssetNode->NextSiblingElement())
	{
		if (gameAssetNode->QueryFloatAttribute("x", &vec.x) || gameAssetNode->QueryFloatAttribute("y", &vec.y)
			|| gameAssetNode->QueryFloatAttribute("angle", &angle))
			throw LoadException(PARSE_ERROR); //Checks all attributes are fetched successfully.
		name = gameAssetNode->Attribute("name");
		if (!name) throw LoadException(PARSE_ERROR);
		texture = aLibrary.get()->Search(name);
		if (!texture) throw LoadException(BAD_SPRITE); //Checks the sprite requested is in the art assets.
		object = gLibrary.get()->Search(name);
		if (!object) throw LoadException(BAD_SPRITE); //Checks the sprite requested is in the object factory.
		object->Initialize(gDevice.get(), iDevice.get(), texture, vec, angle);
		objects.push_back(std::move(object));
		}
	return true;
}


//Load object file and add assets from attributes. Raises LoadException if an error occurs.
bool Game::LoadArtAssets(std::string objectConfigFile)
{
	TiXmlDocument doc;
	TiXmlElement* itemNode;
	const char *attr_name, *attr_path;

	//Tries to open the level configFile, raises an error if it cannot
	if (!doc.LoadFile(objectConfigFile.c_str())) throw LoadException(LOAD_ERROR);
	itemNode = TiXmlHandle(doc.RootElement()).FirstChild("Item").Element();
	if (!itemNode) throw LoadException(PARSE_ERROR);
	for (itemNode; itemNode; itemNode = itemNode->NextSiblingElement())
	{
		attr_name = itemNode->Attribute("name");
		attr_path = itemNode->Attribute("sprite");
		if (!attr_name || !attr_path) throw LoadException(PARSE_ERROR); //Checks attributes exist
		aLibrary->AddAsset(attr_name, attr_path);
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
	for (std::vector<std::unique_ptr<Object>>::iterator it = objects.begin(); it != objects.end(); it++)
		it->get()->Update(0.0);
	return false;
}

//Draw all sprites
void Game::Draw()
{
	gDevice->Begin();
	for (std::vector<std::unique_ptr<Object>>::iterator it = objects.begin(); it != objects.end(); it++)
		it->get()->Draw(0.0, view.get());
	gDevice->Present();
}
