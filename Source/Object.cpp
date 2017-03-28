#include "Object.h"

void Object::addComponent(std::shared_ptr<Component> component)
{
	components.push_back(std::move(component));
}

template<class T>
std::shared_ptr<T> Object::GetComponent()
{
	for (auto comp : components)
	{
		std::shared_ptr<T> target;
		if ((target = std::dynamic_pointer_cast<T>(comp)))
		{
			return(target);
		}
	}

	//Return NULL;
	return(std::shared_ptr<T>());
}
