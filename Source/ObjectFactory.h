#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <map>
#include <memory>
#include <vector>
#include "Definitions.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

class AssetLibrary;
class Component;
class PhysicsDevice;
class Object;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory() {}
	bool Initialize(std::unique_ptr<AssetLibrary> const&, std::unique_ptr<PhysicsDevice> const&);
	void loadPhysics(std::unique_ptr<Object> const&, GAME_OBJECTFACTORY_INITIALIZERS const&);
	std::unique_ptr<Object> create(TiXmlElement*);
	std::unique_ptr<Object> createArrow(Object*, GAME_FLT);
	std::unique_ptr<Object> createAnchor(GAME_VEC);
	std::unique_ptr<Object> createLever(GAME_VEC, GAME_FLT);
	
private:
	std::unique_ptr<Object> create(std::vector<std::string>&, GAME_OBJECTFACTORY_INITIALIZERS const&);
	std::unique_ptr<Component> Search(std::string const&, std::unique_ptr<Object> const&);

private:
	std::map<std::string, COMPONENT_TYPE>	cLibrary;
	AssetLibrary* aLibrary;
	PhysicsDevice*	pDevice;
};

#endif // !OBJECTFACTORY_H
