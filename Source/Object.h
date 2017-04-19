#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>

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
	std::unique_ptr<Object> Update();
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
	std::string getType() { return type; }
	std::shared_ptr<Texture>	getTexture();
	void setType(std::string t) { type = t; }
	void setPhysics(PhysicsDevice* p) { pDevice = p; }

protected:
	std::vector<std::unique_ptr<Component>>	components;
	std::string type;
	bool dead;

public:
	PhysicsDevice*	pDevice;
};

#endif // !OBJECT_H
