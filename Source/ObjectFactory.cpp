#include "ObjectFactory.h"
#include "ArtAssetLibrary.h"
#include "PhysicsDevice.h"
#include "BodyComponentFactory.h"
#include "SpriteComponentFactory.h"
#include "SlideBehaviorComponentFactory.h"
#include "CircleBehaviorComponentFactory.h.h"
#include "Object.h"
#include "PlayerInputComponentFactory.h"
#include "TimedLifeComponentFactory.h"
#include "ArrowBehaviorComponentFactory.h"
#include "Exceptions.h"

ObjectFactory::ObjectFactory()
{
	cLibrary["Body"] = std::make_unique<BodyComponentFactory>();
	cLibrary["Sprite"] = std::make_unique<SpriteComponentFactory>();
	cLibrary["Slide"] = std::make_unique<SlideBehaviorComponentFactory>();
	cLibrary["Circle"] = std::make_unique<CircleBehaviorComponentFactory>();
	cLibrary["Input"] = std::make_unique<PlayerInputComponentFactory>();
	cLibrary["TimedLife"] = std::make_unique<TimedLifeComponentFactory>();
	cLibrary["Arrow"] = std::make_unique<ArrowBehaviorComponentFactory>();
}

//Return an instance of the requested component if it is in the factory, nullptr otherwise.
std::unique_ptr<Component> ObjectFactory::Search(std::string const& component, std::unique_ptr<Object> const& owner)
{
	std::map<std::string, std::unique_ptr<ComponentFactory>>::iterator it = cLibrary.find(component);
	return (it == cLibrary.end()) ? nullptr : it->second->create(owner);
}

bool ObjectFactory::Initialize(std::unique_ptr<ArtAssetLibrary> const& aL, std::unique_ptr<PhysicsDevice> const& pD)
{
	aLibrary = aL.get();
	pDevice = pD.get();
	return true;
}

//Create an object based on data read from gameAssetNode
std::unique_ptr<Object> ObjectFactory::create(TiXmlElement *gameAssetNode)
{
	TiXmlElement* componentNode;
	std::vector<std::string>	componentNames;
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;;

	GOI.name = gameAssetNode->Attribute("name");
	GOI.pos.x = 0.0f;
	GOI.pos.y = 0.0f;
	GOI.angle = 0.0f;
	GOI.radius = false;
	GOI.vertical = false;
	componentNode = TiXmlHandle(gameAssetNode).FirstChild("Component").Element();
	if (!componentNode) throw LoadException(PARSE_ERROR);
	for (componentNode; componentNode; componentNode = componentNode->NextSiblingElement())
	{
		componentNames.push_back(componentNode->Attribute("name"));
		componentNode->QueryFloatAttribute("x", &GOI.pos.x);
		componentNode->QueryFloatAttribute("y", &GOI.pos.y);
		componentNode->QueryFloatAttribute("angle", &GOI.angle);
		componentNode->QueryBoolAttribute("radius", &GOI.radius);
		componentNode->QueryBoolAttribute("vertical", &GOI.vertical);
	}
	return create(componentNames, GOI);
}

//Create arrow from player Object
std::unique_ptr<Object> ObjectFactory::createArrow(Object *player)
{
	std::unique_ptr<Object>	arrow;
	std::vector<std::string>	componentNames = { "Body", "Sprite", "TimedLife", "Arrow" };
	BodyComponent*	link_body = player->GetComponent<BodyComponent>();
	SpriteComponent*	link_sprite = player->GetComponent<SpriteComponent>();
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;
	GAME_VEC link_pos = link_body->getPosition();
	GAME_FLT angle = link_body->getAngle();

	GOI.name = "Arrow";
	GOI.pos.x = link_pos.x;
	GOI.pos.y = link_pos.y;
	GOI.angle = -(angle - PI_2) * 180 / PI;
	GOI.movement_angle = angle;
	GOI.arrow_health = ARROW_HEALTH;
	GOI.arrow_decrement = ARROW_HEALTH_DECREMENT;
	GOI.arrow_movement = ARROW_MOVEMENT;
	arrow = create(componentNames, GOI);
	arrow->GetComponent<SpriteComponent>()->Initialize(link_sprite->getGDevice(), aLibrary->Search("Arrow"));
	loadPhysics(arrow);
	return arrow;
}

//Create each component, call their Initialize method and add them to the new object
std::unique_ptr<Object> ObjectFactory::create(std::vector<std::string>& componentNames, GAME_OBJECTFACTORY_INITIALIZERS const& GOI)
{
	std::unique_ptr<Object>		object = std::make_unique<Object>();
	std::unique_ptr<Component>	component;

	for (std::vector<std::string>::iterator it = componentNames.begin(); it != componentNames.end(); ++it)
	{
		component = Search(*it, object);
		if (component)
		{
			component->Initialize(GOI);
			object->addComponent(std::move(component));
		}
	}
	object->setType(GOI.name);
	return object;
}

void ObjectFactory::loadPhysics(std::unique_ptr<Object> const& object)
{
	std::string type = object->getType();
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;

	GOI.body_type = GAME_DYNAMIC;
	GOI.shape = GAME_CIRCLE;
	GOI.width = (GAME_FLT)object->getTexture()->getWidth() / 2.0f;
	GOI.height = 1.0f;
	GOI.density = 2.0f;
	GOI.friction = 0.0f;
	GOI.restitution = 4.0f;
	GOI.angularDamping = 0.0f;
	GOI.linearDamping = 0.0f;
	if (type == "Link")
	{
		GOI.density = 1.0f;
		GOI.friction = 0.3f;
		GOI.restitution = 18.0f;
		GOI.angularDamping = 10.0f;
		GOI.linearDamping = 1.0f;
	}
	if (type.find("Leever"))
	{
		GOI.shape = GAME_RECTANGLE;
		GOI.width = (GAME_FLT)object->getTexture()->getWidth();
		GOI.height = (GAME_FLT)object->getTexture()->getHeight();
		GOI.friction = 0.9f;
		GOI.angularDamping = 5.0f;
		GOI.linearDamping = 0.1f;
	}
	if (type == "Rock")
	{
		GOI.body_type = GAME_STATIC;
		GOI.density = 25.0f;
		GOI.restitution = 20.0f;
	}
	if (type.find("Octorok"))
	{
		GOI.density = 13.0f;
		GOI.friction = 0.9f;
		GOI.angularDamping = 20.0f;
	}
	if (type == "Arrow")
	{
		GOI.shape = GAME_RECTANGLE;
		GOI.width = (GAME_FLT)object->getTexture()->getWidth();
		GOI.height = (GAME_FLT)object->getTexture()->getHeight();
		GOI.density = 0.5f;
		GOI.restitution = 1.0f;
	}
	pDevice->CreateFixture(object.get(), GOI);
}