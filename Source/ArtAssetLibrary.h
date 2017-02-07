#ifndef  ARTASSETLIBRARY_H
#define ARTASSETLIBRARY_H

#include <map>
#include <memory>
#include "Texture.h"

class ArtAssetLibrary
{
public:
	ArtAssetLibrary() {}
	~ArtAssetLibrary() {}
	bool AddAsset(std::string, std::string);
	std::shared_ptr<Texture> Search(std::string);

private:
	std::map<std::string, std::shared_ptr<Texture>> library;
	GraphicsDevice* gDevice;
};

#endif // ! ARTASSETLIBRARY_H
