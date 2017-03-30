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
	std::unique_ptr<Object>	r = NULL;

	for (auto comp : components)
	{
		o = comp->Update();
		if (o)
			r = std::move(o);
		if (comp->Finish())
			dead = true;
	}
	return r;
}

void Object::addComponent(std::shared_ptr<Component> component)
{
	components.push_back(std::move(component));
}
