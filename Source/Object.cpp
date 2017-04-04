#include "Object.h"
#include "Component.h"

Object::Object()
{
	dead = false;
}

Object::~Object()
{

}

std::unique_ptr<Object> Object::Update()
{
	std::unique_ptr<Object>	new_object = nullptr;
	std::unique_ptr<Object> o;

	for (auto const& component : components)
	{
		o = component->Update();
		if (o)
			new_object = std::move(o);
		if (component->Finish())
			dead = true;
	}
	return new_object;
}

void Object::addComponent(std::unique_ptr<Component> component)
{
	components.push_back(std::move(component));
}
