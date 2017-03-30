#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "Texture.h"
#include "View.h"

class Component;

//Abstract object class, enemies inherit from this class
class Object
{
public:
	Object();
	~Object();
	std::unique_ptr<Object> Update();
	void addComponent(std::shared_ptr<Component>);
	template<class T>
	std::shared_ptr<T> GetComponent()
	{
		for (auto comp : components)
		{
			std::shared_ptr<T> target;
			if ((target = std::dynamic_pointer_cast<T>(comp)))
			{
				return(target);
			}
		}
		return NULL;
	}
	bool isDead() { return dead; }

protected:
	std::vector<std::shared_ptr<Component>>	components;
	bool dead;
};

#endif // !OBJECT_H
