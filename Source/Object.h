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
	bool isDead() { return dead; }
	Object* getParent() { return parent; }
	std::string getType() { return type; }
	std::shared_ptr<Texture>	getTexture();
	void setType(std::string t) { type = t; }
	void setPhysics(PhysicsDevice* p) { pDevice = p; }
	void setParent(Object* o) { parent = o; }
	void setChild(Object* o) { child = o; }
	bool hasChild() { return (child); }

protected:
	std::vector<std::unique_ptr<Component>>	components;
	std::string type;
	bool dead;
	Object* parent;
	Object* child;

public:
	PhysicsDevice*	pDevice;
};

#endif // !OBJECT_H
