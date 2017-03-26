#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <map>
#include <memory>
#include "ComponentFactory.h"
#include "Object.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

class ObjectFactory
{
public:
	ObjectFactory();
	std::unique_ptr<Object> create(TiXmlElement*);

private:
	std::unique_ptr<Object> create(std::vector<std::string>&, GAME_OBJECTFACTORY_INITIALIZERS&);
	std::unique_ptr<Component> Search(std::string&, std::unique_ptr<Object>&);

private:
	std::map<std::string, std::unique_ptr<ComponentFactory>>	cLibrary;
};

#endif // !OBJECTFACTORY_H
