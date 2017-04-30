#include <iostream>
#include "AssetLibrary.h"
#include "GraphicsDevice.h"
#include "Exceptions.h"
#include "Texture.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

//Load all sprites from their path contained in the argument
bool AssetLibrary::LoadArt(std::string objectConfigFile)
{
	TiXmlDocument doc;
	TiXmlElement* itemNode;
	const char *attr_name, *attr_path;

	//Tries to open the configFile, raises an error if it cannot
	if (!doc.LoadFile(objectConfigFile.c_str())) throw LoadException(LOAD_ERROR, objectConfigFile);
	itemNode = TiXmlHandle(doc.RootElement()).FirstChild("Item").Element();
	if (!itemNode) throw LoadException(PARSE_ERROR, objectConfigFile);
	for (itemNode; itemNode; itemNode = itemNode->NextSiblingElement())
	{
		attr_name = itemNode->Attribute("name");
		attr_path = itemNode->Attribute("sprite");
		if (!attr_name || !attr_path) throw LoadException(PARSE_ERROR, objectConfigFile); //Checks attributes exist
		AddArtAsset(attr_name, attr_path);
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

//Make texture object from object file
bool AssetLibrary::AddArtAsset(std::string name, std::string path)
{
	std::shared_ptr<Texture>	t(new Texture());

	if (!t->load(gDevice->getRenderer(), path))
		return false;
	artLibrary[name] = t;
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

//Return an instance of the requested GOI if it is in the library, nullptr otherwise.
std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>	AssetLibrary::SearchPhysics(std::string name)
{
	for (auto item : physicsLibrary)
	{
		if (name.find(item.first) != std::string::npos)
			return item.second;
	}
	return nullptr;
}
