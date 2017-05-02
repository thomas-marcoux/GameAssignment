#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>
#include "Definitions.h"

class Component;
class GraphicsDevice;
class InputDevice;
class PhysicsDevice;
class Texture;
class View;

//Game Actor class
class Object
{
public:
	Object();
	~Object();
	std::unique_ptr<Object> Update(GAME_FLT);
	void addComponent(std::unique_ptr<Component>);
	template<class T>
	T* GetComponent()
	{
		for (auto const& comp : components)
		{
			T* target;
			if ((target = dynamic_cast<T*>(comp.get())))
			{
				return(target);
			}
		}
		return NULL;
	}
	void kill();
	bool isDead();
	Object* getParent() { return parent; }
	std::string getName() { return name; }
	OBJECT_TYPE getType() { return type; }
	std::shared_ptr<Texture>	getTexture();
	void setType(std::string t);
	void setPhysics(PhysicsDevice* p) { pDevice = p; }
	void setParent(Object* o) { parent = o; }
	void setChild(Object* o) { child = o; }
	bool hasChild() { return (child) ? true : false; }

protected:
	std::vector<std::unique_ptr<Component>>	components;
	std::string name;
	OBJECT_TYPE	type;
	bool dead;
	Object* parent;
	Object* child;

public:
	PhysicsDevice*	pDevice;
};

#endif // !OBJECT_H
