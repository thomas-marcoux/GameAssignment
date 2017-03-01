#ifndef  ARTASSETLIBRARY_H
#define ARTASSETLIBRARY_H

#include <map>
#include <memory>
#include "GraphicsDevice.h"
#include "Texture.h"

//Stores object textures
class ArtAssetLibrary
{
public:
	ArtAssetLibrary(GraphicsDevice* gD) : gDevice(gD) {}
	~ArtAssetLibrary() {}
	bool AddAsset(std::string, std::string);
	std::shared_ptr<Texture> Search(std::string);

private:
	std::map<std::string, std::shared_ptr<Texture>> library;
	GraphicsDevice* gDevice;
};

#endif // ! ARTASSETLIBRARY_H
