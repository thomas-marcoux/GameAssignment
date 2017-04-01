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

protected:
	std::vector<std::unique_ptr<Component>>	components;
	bool dead;
};

#endif // !OBJECT_H
