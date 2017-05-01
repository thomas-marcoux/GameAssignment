#ifndef  ASSETLIBRARY_H
#define ASSETLIBRARY_H

#include <map>
#include <memory>
#include <vector>
#include "Definitions.h"
#include "SDL_Mixer.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

class GraphicsDevice;
class SoundDevice;
class Texture;

//Stores Game assets
class AssetLibrary
{
public:
	AssetLibrary(GraphicsDevice* gD, SoundDevice* sD) : gDevice(gD), sDevice(sD) {}
	~AssetLibrary();
	bool LoadArt(std::string);
	bool LoadMusic(std::string);
	bool LoadObject(TiXmlElement*);
	bool LoadPhysics(std::string);
	bool LoadSoundEffects(std::string);
	bool AddArtAsset(std::string, std::string);
	bool AddMusicAsset(std::string, std::string);
	bool AddSoundEffectAsset(std::string, std::string);
	bool AddPhysicsAsset(std::string const&, GAME_OBJECTFACTORY_INITIALIZERS const&);
	std::shared_ptr<Texture> SearchArt(std::string);
	Mix_Chunk* SearchSound(std::string);
	Mix_Music* SearchMusic(std::string);
	std::shared_ptr<std::vector<std::string>>	SearchComponents(std::string);
	std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>	SearchParameters(std::string);
	std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>	SearchPhysics(std::string);

private:
	GAME_BODY_TYPE	getBodyType(std::string const&);
	GAME_OBJECT_SHAPE	getShape(std::string const&);
	bool getBoolean(std::string const&);

private:
	std::map<std::string, std::shared_ptr<Texture>> artLibrary;
	std::map<std::string, std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>> physicsLibrary;
	std::map<std::string, std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>> parametersLibrary;
	std::map<std::string, std::shared_ptr<std::vector<std::string>>>	componentsLibrary;
	std::map<std::string, Mix_Chunk*> soundEffectLibrary;
	std::map<std::string, Mix_Music*> musicLibrary;
	GraphicsDevice* gDevice;
	SoundDevice* sDevice;
};

#endif // ! ASSETLIBRARY_H
