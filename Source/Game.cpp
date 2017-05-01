#include <algorithm>
#include <fstream>
#include <sstream>
#include "Game.h"
#include "CircleBehaviorComponent.h"
#include "SpriteComponent.h"
#include "PlayerInputComponent.h"
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
		&& oFactory->Initialize(aLibrary, pDevice))
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
		sprite->Initialize(gDevice.get(), aLibrary->SearchArt(name));
		if (name == "Link")
		{
			sprite->LoadTexture(TEXTURE_UP, aLibrary->SearchArt("Link Up"));
			sprite->LoadTexture(TEXTURE_DOWN, aLibrary->SearchArt("Link Down"));
			sprite->LoadTexture(TEXTURE_LEFT, aLibrary->SearchArt("Link Left"));
			sprite->LoadTexture(TEXTURE_RIGHT, aLibrary->SearchArt("Link Right"));
			sprite->UpdateTexture(TEXTURE_UP);
		}	
	}
	return true;
}

//Create Joints for CircleBehavior Components
bool Game::LoadJoints()
{
	CircleBehaviorComponent *component;
	for (auto const& object : objects)
	{
		component = object->GetComponent<CircleBehaviorComponent>();
		if (component)
			component->Initialize(oFactory.get());
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

bool Game::LoadMap(std::string const& mapFile)
{
	std::ifstream file;
	std::unique_ptr<Object> new_object = nullptr;
	GAME_VEC	start = { 50, 50 };
	GAME_VEC	increment = { SPRITE_WIDTH, SPRITE_HEIGHT };
	GAME_VEC	coord;
	std::string	line;

	file.open(mapFile);
	if (!file.is_open())
		throw LoadException(LOAD_ERROR, mapFile);
	coord.y = start.y;
	while (std::getline(file, line))
	{
		coord.x = start.x;
		for (int i = 0; i < line.size(); i++)
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



//Loads game info from both config files, catches errors occuring during loading
bool Game::LoadLevel(std::string levelConfigFile, std::string objectConfigFile, std::string physicsConfigFile,
	std::string spritesConfigFile)
{
	try
	{
		view = std::make_unique<View>();
		view->Initialize(iDevice.get(), 0, 0);
		LoadAssets(spritesConfigFile, physicsConfigFile, "./Assets/Config/sounds.xml", "./Assets/Config/music.xml");
		//LoadGameAssets(levelConfigFile);
		LoadObjects(objectConfigFile);
		LoadMap("./Assets/Config/bomberman_level_1.map");
		LoadSprites();
		LoadPlayer();
		LoadJoints();
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
	int id = 0;

	if (!view->Update())
		return true;
	for (auto object = objects.begin(); object != objects.end(); object++, id++)
	{
		r = std::move((*object)->Update(dt));
		if ((*object)->isDead()) //If object is dead, store its ID to be deleted
			deadObjectIDs.push_back(id);
		if (r)
			new_object = std::move(r);
	}
	pDevice->Update(dt);
	if (new_object) //If a new object has been created, add it to the vector
		objects.push_back(std::move(new_object));
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
}

//Draw all sprites
void Game::Draw()
{
	gDevice->Begin();
	gDevice->Draw(view.get());
	gDevice->Present();
}
