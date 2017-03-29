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
	Object() {}
	~Object() { /*components.clear();*/ }
	void Update();
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

protected:
	std::vector<std::shared_ptr<Component>>	components;
};

#endif // !OBJECT_H
