#include "Object.h"
#include "Component.h"

void Object::Update()
{
	for (auto comp : components)
		comp->Update();
}

void Object::addComponent(std::shared_ptr<Component> component)
{
	components.push_back(std::move(component));
}
