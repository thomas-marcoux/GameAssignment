#ifndef  ASSETLIBRARY_H
#define ASSETLIBRARY_H

#include <map>
#include <memory>
#include "Definitions.h"

class GraphicsDevice;
class Texture;

//Stores object textures
class AssetLibrary
{
public:
	AssetLibrary(GraphicsDevice* gD) : gDevice(gD) {}
	~AssetLibrary() {}
	bool LoadArt(std::string);
	bool LoadPhysics(std::string);
	bool AddArtAsset(std::string, std::string);
	bool AddPhysicsAsset(std::string const&, GAME_OBJECTFACTORY_INITIALIZERS const&);
	std::shared_ptr<Texture> SearchArt(std::string);
	std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>	SearchPhysics(std::string);

private:
	GAME_BODY_TYPE	getBodyType(char const*);
	GAME_OBJECT_SHAPE	getShape(char const*);

private:
	std::map<std::string, std::shared_ptr<Texture>> artLibrary;
	std::map <std::string, std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>> physicsLibrary;
	GraphicsDevice* gDevice;
};

#endif // ! ASSETLIBRARY_H
