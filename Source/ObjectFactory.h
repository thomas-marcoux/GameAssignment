#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <map>
#include <memory>
#include "ComponentFactory.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

class ArtAssetLibrary;
class PhysicsDevice;
class Object;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory() {}
	bool Initialize(std::unique_ptr<ArtAssetLibrary> const&, std::unique_ptr<PhysicsDevice> const&);
	void loadPhysics(std::unique_ptr<Object> const&);
	std::unique_ptr<Object> create(TiXmlElement*);
	std::unique_ptr<Object> createArrow(Object*);
	
private:
	std::unique_ptr<Object> create(std::vector<std::string>&, GAME_OBJECTFACTORY_INITIALIZERS const&);
	std::unique_ptr<Component> Search(std::string const&, std::unique_ptr<Object> const&);

private:
	std::map<std::string, std::unique_ptr<ComponentFactory>>	cLibrary;
	ArtAssetLibrary* aLibrary;
	PhysicsDevice*	pDevice;
};

#endif // !OBJECTFACTORY_H
