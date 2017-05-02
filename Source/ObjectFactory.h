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
class Game;
class PhysicsDevice;
class SoundDevice;
class Object;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory() {}
	bool Initialize(Game*, std::unique_ptr<AssetLibrary> const&, std::unique_ptr<PhysicsDevice> const&, std::unique_ptr<SoundDevice> const&);
	void loadPhysics(std::unique_ptr<Object> const&, GAME_OBJECTFACTORY_INITIALIZERS const&);
	std::unique_ptr<Object> create(std::string const&, GAME_VEC const&);
	std::unique_ptr<Object> createArrow(Object*);
	std::unique_ptr<Object> createBomb(Object*);
	std::unique_ptr<Object> createBlast(Object*);
	std::unique_ptr<Object> createAnchor(GAME_VEC);
	std::unique_ptr<Object> createLever(GAME_VEC, GAME_FLT);
	void queueObject(std::unique_ptr<Object>);
	
private:
	std::unique_ptr<Object> create(std::vector<std::string>&, GAME_OBJECTFACTORY_INITIALIZERS const&);
	std::unique_ptr<Component> Search(std::string const&, std::unique_ptr<Object> const&);

private:
	std::map<std::string, COMPONENT_TYPE>	cLibrary;
	AssetLibrary* aLibrary;
	PhysicsDevice*	pDevice;
	SoundDevice*	sDevice;
	Game*			game;
};

#endif // !OBJECTFACTORY_H
