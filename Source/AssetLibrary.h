#ifndef  ASSETLIBRARY_H
#define ASSETLIBRARY_H

#include <map>
#include <memory>

class GraphicsDevice;
class Texture;

//Stores object textures
class AssetLibrary
{
public:
	AssetLibrary(GraphicsDevice* gD) : gDevice(gD) {}
	~AssetLibrary() {}
	bool AddAsset(std::string, std::string);
	std::shared_ptr<Texture> Search(std::string);

private:
	std::map<std::string, std::shared_ptr<Texture>> library;
	GraphicsDevice* gDevice;
};

#endif // ! ASSETLIBRARY_H
