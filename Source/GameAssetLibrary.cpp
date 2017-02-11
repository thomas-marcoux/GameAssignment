#include "GameAssetLibrary.h"
#include "BlueOctorokFactory.h"
#include "RedOctorokFactory.h"
#include "BlueLeeverFactory.h"
#include "RedLeeverFactory.h"

GameAssetLibrary::GameAssetLibrary()
{
	/*
	library["Blue Octorok"] = (std::unique_ptr<ObjectFactory>)(new BlueOctorokFactory());
	library["Red Octorok"] = (std::unique_ptr<ObjectFactory>)(new RedOctorokFactory());
	library["Blue Leever"] = (std::unique_ptr<ObjectFactory>)(new BlueLeeverFactory());
	library["Red Leever"] = (std::unique_ptr<ObjectFactory>)(new RedLeeverFactory());
	*/
	library["Blue Octorok"] = (std::make_unique<BlueOctorokFactory>());
	library["Red Octorok"] = (std::make_unique<RedOctorokFactory>());
	library["Blue Leever"] = (std::make_unique<BlueLeeverFactory>());
	library["Red Leever"] = (std::make_unique<RedLeeverFactory>());
}

//Return an instance of the requested object if it is in the factory, NULL otherwise.
std::unique_ptr<Object> GameAssetLibrary::Search(std::string object)
{
	std::map<std::string, std::unique_ptr<ObjectFactory>>::iterator it = library.find(object);
	return (it == library.end()) ? NULL : it->second->create();
}
