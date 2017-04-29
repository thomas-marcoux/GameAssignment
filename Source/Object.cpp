#include "Object.h"
#include "Component.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "View.h"

Object::Object()
{
	name = "null";
	type = DEFAULT_TYPE;
	dead = false;
	child = nullptr;
	parent = nullptr;
}

Object::~Object()
{

}

//Call each Component's update method, if one returns a new object, returns it. If a Component's Finish method returns true, kill the object
std::unique_ptr<Object> Object::Update(GAME_FLT dt)
{
	std::unique_ptr<Object>	new_object = nullptr;
	std::unique_ptr<Object> o;

	for (auto const& component : components)
	{
		o = component->Update(dt);
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

std::shared_ptr<Texture> Object::getTexture()
{
	return GetComponent<SpriteComponent>()->getTexture();
}

void Object::setType(std::string t)
{
	name = t;
	type = DEFAULT_TYPE;
	if (name == "Arrow")
		type = ARROW_TYPE;
	if (name == "Link")
		type = PLAYER_TYPE;
	if (name == "Rock")
		type = ROCK_TYPE;
	if (name.find("Leever") != std::string::npos)
		type = LEEVER_TYPE;
	if (name.find("Octorock") != std::string::npos)
		type = OCTOROCK_TYPE;
}
