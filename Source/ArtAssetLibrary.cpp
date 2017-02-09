#include "ArtAssetLibrary.h"

bool ArtAssetLibrary::AddAsset(std::string name, std::string path)
{
	std::shared_ptr<Texture>	t(new Texture());

	if (!t->load(gDevice->getRenderer(), path))
		return false;
	library[name] = t;
	return true;
}

std::shared_ptr<Texture> ArtAssetLibrary::Search(std::string name)
{
	return library.find(name)->second;
}
