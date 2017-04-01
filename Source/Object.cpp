#include "Object.h"
#include "Component.h"

Object::Object()
{
	dead = false;
}

Object::~Object()
{
	components.clear();
}

std::unique_ptr<Object> Object::Update()
{
	std::unique_ptr<Object>	o;
	std::unique_ptr<Object>	r;
	
	for (auto const& component : components)
	{
		o = component->Update();
		if (o)
			r = std::move(o);
		if (component->Finish())
			dead = true;
	}
	return (r) ? std::move(r) : nullptr;
}

void Object::addComponent(std::unique_ptr<Component> component)
{
	components.push_back(std::move(component));
}
