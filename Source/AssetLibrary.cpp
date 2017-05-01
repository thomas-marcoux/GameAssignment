#include <iostream>
#include "AssetLibrary.h"
#include "GraphicsDevice.h"
#include "Exceptions.h"
#include "Texture.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

//Free SDL_Mixer ressources
AssetLibrary::~AssetLibrary()
{
	for (auto it : soundEffectLibrary)
		Mix_FreeChunk(it.second);
	for (auto it : musicLibrary)
		Mix_FreeMusic(it.second);
}

//Load all sprites from their path contained in the argument
bool AssetLibrary::LoadArt(std::string file)
{
	TiXmlDocument doc;
	TiXmlElement* itemNode;
	const char *attr_name, *attr_path;

	//Tries to open the configFile, raises an error if it cannot
	if (!doc.LoadFile(file.c_str())) throw LoadException(LOAD_ERROR, file);
	itemNode = TiXmlHandle(doc.RootElement()).FirstChild("Item").Element();
	if (!itemNode) throw LoadException(PARSE_ERROR, file);
	for (itemNode; itemNode; itemNode = itemNode->NextSiblingElement())
	{
		attr_name = itemNode->Attribute("name");
		attr_path = itemNode->Attribute("sprite");
		if (!attr_name || !attr_path) throw LoadException(PARSE_ERROR, file); //Checks attributes exist
		AddArtAsset(attr_name, attr_path);
	}
	return true;
}

//Load musics
bool AssetLibrary::LoadMusic(std::string file)
{
	TiXmlDocument doc;
	TiXmlElement* itemNode;
	const char *attr_name, *attr_path;

	//Tries to open the configFile, raises an error if it cannot
	if (!doc.LoadFile(file.c_str())) throw LoadException(LOAD_ERROR, file);
	itemNode = TiXmlHandle(doc.RootElement()).FirstChild("Item").Element();
	if (!itemNode) throw LoadException(PARSE_ERROR, file);
	for (itemNode; itemNode; itemNode = itemNode->NextSiblingElement())
	{
		attr_name = itemNode->Attribute("name");
		attr_path = itemNode->Attribute("audio");
		if (!attr_name || !attr_path) throw LoadException(PARSE_ERROR, file); //Checks attributes exist
		if (!AddMusicAsset(attr_name, attr_path)) throw LoadException(LOAD_ERROR, attr_path);
	}
	return true;
}

bool AssetLibrary::LoadObject(TiXmlElement* gameAssetNode)
{
	TiXmlElement* componentNode;
	std::vector<std::string>	componentNames;
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;
	std::string ID;

	ID = gameAssetNode->Attribute("ID");
	if (ID.empty())
		return false;
	GOI.name = gameAssetNode->Attribute("name");
	GOI.vertical = false;
	componentNode = TiXmlHandle(gameAssetNode).FirstChild("Component").Element();
	for (componentNode; componentNode; componentNode = componentNode->NextSiblingElement())
	{
		componentNames.push_back(componentNode->Attribute("name"));
		componentNode->QueryBoolAttribute("vertical", &GOI.vertical);
	}
	AddObject(ID, componentNames, GOI);
	return true;
}

//Loads all physics information
bool AssetLibrary::LoadPhysics(std::string physicsConfigFile)
{
	TiXmlDocument doc;
	TiXmlElement* itemNode;

	//Tries to open the configFile, raises an error if it cannot
	if (!doc.LoadFile(physicsConfigFile.c_str())) throw LoadException(LOAD_ERROR, physicsConfigFile);
	itemNode = TiXmlHandle(doc.RootElement()).FirstChild("Item").Element();
	if (!itemNode) throw LoadException(PARSE_ERROR, physicsConfigFile);
	for (itemNode; itemNode; itemNode = itemNode->NextSiblingElement())
	{
		GAME_OBJECTFACTORY_INITIALIZERS	GOI;
		const char *name = nullptr;
		name = itemNode->Attribute("name");
		if (!name) throw LoadException(PARSE_ERROR, physicsConfigFile);
		GOI.body_type = getBodyType(itemNode->Attribute("type"));
		GOI.shape = getShape(itemNode->Attribute("shape"));
		GOI.collision = getBoolean(itemNode->Attribute("collision"));
		GOI.rotation = getBoolean(itemNode->Attribute("rotation"));
		itemNode->QueryFloatAttribute("density", &GOI.density);
		itemNode->QueryFloatAttribute("friction", &GOI.friction);
		itemNode->QueryFloatAttribute("restitution", &GOI.restitution);
		itemNode->QueryFloatAttribute("angular", &GOI.angularDamping);
		itemNode->QueryFloatAttribute("linear", &GOI.linearDamping);
		AddPhysicsAsset(name, GOI);
	}
	return true;
}

//Loads sound effects
bool AssetLibrary::LoadSoundEffects(std::string file)
{
	TiXmlDocument doc;
	TiXmlElement* itemNode;
	const char *attr_name, *attr_path;

	//Tries to open the configFile, raises an error if it cannot
	if (!doc.LoadFile(file.c_str())) throw LoadException(LOAD_ERROR, file);
	itemNode = TiXmlHandle(doc.RootElement()).FirstChild("Item").Element();
	if (!itemNode) throw LoadException(PARSE_ERROR, file);
	for (itemNode; itemNode; itemNode = itemNode->NextSiblingElement())
	{
		attr_name = itemNode->Attribute("name");
		attr_path = itemNode->Attribute("audio");
		if (!attr_name || !attr_path) throw LoadException(PARSE_ERROR, file); //Checks attributes exist
		if (!AddSoundEffectAsset(attr_name, attr_path)) throw LoadException(LOAD_ERROR, attr_path);
	}
	return true;
}

//Translates text to body_type, default is static
GAME_BODY_TYPE	AssetLibrary::getBodyType(std::string const& type)
{
	if (type.empty()) throw LoadException(PARSE_ERROR, "physicsConfigFile");
	if (type == "dynamic")
		return GAME_DYNAMIC;
	if (type == "kinematic")
		return GAME_KINEMATIC;
	return GAME_STATIC;
}

//Translates text to object_shape, default is circle
GAME_OBJECT_SHAPE AssetLibrary::getShape(std::string const& shape)
{
	if (shape.empty()) throw LoadException(PARSE_ERROR, "physicsConfigFile");
	if (shape == "rectangle")
		return GAME_RECTANGLE;
	return GAME_CIRCLE;
}

//Reads collision boolean, defaults to true (detects collision)
bool AssetLibrary::getBoolean(std::string const& attribute)
{
	if (attribute.empty()) throw LoadException(PARSE_ERROR, "physicsConfigFile");
	if (attribute == "false")
		return false;
	return true;;
}

//Make texture object from object file
bool AssetLibrary::AddArtAsset(std::string name, std::string path)
{
	std::shared_ptr<Texture>	t(new Texture());

	if (!t->load(gDevice->getRenderer(), path))
		return false;
	artLibrary[name] = t;
	return true;
}

bool AssetLibrary::AddMusicAsset(std::string name, std::string path)
{
	Mix_Music* music = Mix_LoadMUS(path.c_str());

	if (!music)
		return false;
	musicLibrary[name] = music;
	return true;
}

bool AssetLibrary::AddObject(std::string ID, std::vector<std::string>& componentNames, GAME_OBJECTFACTORY_INITIALIZERS const& GOI)
{
	componentsLibrary[ID] = std::make_shared<std::vector<std::string>>(componentNames);
	parametersLibrary[ID] = std::make_shared<GAME_OBJECTFACTORY_INITIALIZERS>(GOI);
	return false;
}

bool AssetLibrary::AddSoundEffectAsset(std::string name, std::string path)
{
	Mix_Chunk* sound = Mix_LoadWAV(path.c_str());

	if (!sound)
		return false;
	soundEffectLibrary[name] = sound;
	return true;
}

//Store GOI in physicsLibrary
bool AssetLibrary::AddPhysicsAsset(std::string const& type, GAME_OBJECTFACTORY_INITIALIZERS const& GOI)
{
	physicsLibrary[type] = std::make_shared<GAME_OBJECTFACTORY_INITIALIZERS>(GOI);
	return true;
}

//Return an instance of the requested Texture if it is in the library, nullptr otherwise.
std::shared_ptr<Texture> AssetLibrary::SearchArt(std::string name)
{
	std::map<std::string, std::shared_ptr<Texture>>::iterator it = artLibrary.find(name);
	return (it == artLibrary.end()) ? nullptr : it->second;
}

Mix_Chunk* AssetLibrary::SearchSound(std::string name)
{
	std::map<std::string, Mix_Chunk*>::iterator it = soundEffectLibrary.find(name);
	return (it == soundEffectLibrary.end()) ? nullptr : it->second;
}

Mix_Music* AssetLibrary::SearchMusic(std::string name)
{
	std::map<std::string, Mix_Music*>::iterator it = musicLibrary.find(name);
	return (it == musicLibrary.end()) ? nullptr : it->second;
}

std::shared_ptr<std::vector<std::string>> AssetLibrary::SearchComponents(std::string name)
{
	std::map<std::string, std::shared_ptr<std::vector<std::string>>>::iterator it = componentsLibrary.find(name);
	return (it == componentsLibrary.end()) ? nullptr : it->second;
}

std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS> AssetLibrary::SearchParameters(std::string name)
{
	std::map<std::string, std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>>::iterator it = parametersLibrary.find(name);
	return (it == parametersLibrary.end()) ? nullptr : it->second;
}

//Return an instance of the requested GOI if it is in the library, nullptr otherwise.
std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>	AssetLibrary::SearchPhysics(std::string name)
{
	std::map<std::string, std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>>::iterator it = physicsLibrary.find(name);
	return (it == physicsLibrary.end()) ? nullptr : it->second;
}
