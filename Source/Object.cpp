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

void Object::kill()
{
	dead = true;
}

bool Object::isDead()
{
	return dead;
}

std::shared_ptr<Texture> Object::getTexture()
{
	return GetComponent<SpriteComponent>()->getTexture();
}

//Set OBJECT_TYPE in accordance with the object's name
void Object::setType(std::string t)
{
	name = t;
	type = DEFAULT_TYPE;
	if (name == "Arrow")
		type = ARROW_TYPE;
	if (name == "Bomb")
		type = BOMB_TYPE;
	if (name == "Blast")
		type = BLAST_TYPE;
	if (name == "Player")
		type = PLAYER_TYPE;
	if (name == "Rock")
		type = ROCK_TYPE;
	if (name == "Exit")
		type = EXIT_TYPE;
	if (name == "Destructible")
		type = DESTRUCTIBLE_TYPE;
	if (name.find("Leever") != std::string::npos)
		type = LEEVER_TYPE;
	if (name.find("Octorok") != std::string::npos)
		type = OCTOROK_TYPE;
	if (name == "Wall")
		type = WALL_TYPE;
	if (name == "Secret Exit")
		type = SECRET_EXIT_TYPE;
}
