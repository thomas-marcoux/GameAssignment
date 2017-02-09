#include "GameAssetLibrary.h"
#include "BlueOctorokFactory.h"
#include "RedOctorokFactory.h"
#include "BlueLeeverFactory.h"
#include "RedLeeverFactory.h"

GameAssetLibrary::GameAssetLibrary()
{
	library["Blue Octorok"] = (std::unique_ptr<ObjectFactory>)(std::unique_ptr<BlueOctorokFactory>());
	library["Red Octorok"] = (std::unique_ptr<ObjectFactory>)(std::unique_ptr<RedOctorokFactory>());
	library["Blue Leever"] = (std::unique_ptr<ObjectFactory>)(std::unique_ptr<BlueLeeverFactory>());
	library["Red Leever"] = (std::unique_ptr<ObjectFactory>)(std::unique_ptr<RedLeeverFactory>());
}

std::unique_ptr<Object> GameAssetLibrary::Search(std::string)
{
	return std::unique_ptr<Object>();
}
