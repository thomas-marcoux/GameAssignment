#ifndef GAMEASSETLIBRARY_H
#define GAMEASSETLIBRARY_H

#include <map>
#include <memory>
#include "ObjectFactory.h"

//Object factory manager
class GameAssetLibrary
{
public:
	GameAssetLibrary();
	~GameAssetLibrary() {}
	std::unique_ptr<Object> Search(std::string);

private:
	std::map<std::string, std::unique_ptr<ObjectFactory>> library;
};

#endif // ! GAMEASSETLIBRARY_H
