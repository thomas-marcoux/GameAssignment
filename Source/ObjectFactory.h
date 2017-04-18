#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <map>
#include <memory>
#include "ComponentFactory.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

class ArtAssetLibrary;
class Object;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory() {}
	bool Initialize(ArtAssetLibrary*);
	std::unique_ptr<Object> create(TiXmlElement*);
	std::unique_ptr<Object> createArrow(Object*);

private:
	std::unique_ptr<Object> create(std::vector<std::string>&, GAME_OBJECTFACTORY_INITIALIZERS const&);
	std::unique_ptr<Component> Search(std::string const&, std::unique_ptr<Object> const&);

private:
	std::map<std::string, std::unique_ptr<ComponentFactory>>	cLibrary;
	ArtAssetLibrary* aLibrary;
};

#endif // !OBJECTFACTORY_H
