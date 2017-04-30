#ifndef  ASSETLIBRARY_H
#define ASSETLIBRARY_H

#include <map>
#include <memory>
#include "Definitions.h"

class GraphicsDevice;
class Texture;

//Stores Game assets
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
	GAME_BODY_TYPE	getBodyType(std::string const&);
	GAME_OBJECT_SHAPE	getShape(std::string const&);
	bool getBoolean(std::string const&);

private:
	std::map<std::string, std::shared_ptr<Texture>> artLibrary;
	std::map <std::string, std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>> physicsLibrary;
	GraphicsDevice* gDevice;
};

#endif // ! ASSETLIBRARY_H
