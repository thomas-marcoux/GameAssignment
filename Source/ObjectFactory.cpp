#include "ObjectFactory.h"
#include "AssetLibrary.h"
#include "Exceptions.h"
#include "Object.h"
#include "PhysicsDevice.h"
#include "ArrowBehaviorComponent.h"
#include "BodyComponent.h"
#include "CircleBehaviorComponent.h"
#include "PlayerInputComponent.h"
#include "TimedLifeComponent.h"
#include "SlideBehaviorComponent.h"
#include "SpriteComponent.h"

ObjectFactory::ObjectFactory()
{
	cLibrary["Body"] = BODY_COMPONENT;
	cLibrary["Sprite"] = SPRITE_COMPONENT;
	cLibrary["Slide"] = SLIDE_COMPONENT;
	cLibrary["Circle"] = CIRCLE_COMPONENT;
	cLibrary["Input"] = INPUT_COMPONENT;
	cLibrary["TimedLife"] = TIMEDLIFE_COMPONENT;
	cLibrary["Arrow"] = ARROW_COMPONENT;
}

//Return an instance of the requested component if it is in the factory, nullptr otherwise.
std::unique_ptr<Component> ObjectFactory::Search(std::string const& component, std::unique_ptr<Object> const& owner)
{
	std::map<std::string, COMPONENT_TYPE>::iterator it = cLibrary.find(component);
	
	if (it == cLibrary.end())
		return nullptr;
	switch (it->second)
	{
	case BODY_COMPONENT:
		return std::make_unique<BodyComponent>(owner);
		break;
	case SPRITE_COMPONENT:
		return std::make_unique<SpriteComponent>(owner);
		break;
	case SLIDE_COMPONENT:
		return std::make_unique<SlideBehaviorComponent>(owner);
		break;
	case CIRCLE_COMPONENT:
		return std::make_unique<CircleBehaviorComponent>(owner);
		break;
	case INPUT_COMPONENT:
		return std::make_unique<PlayerInputComponent>(owner);
		break;
	case TIMEDLIFE_COMPONENT:
		return std::make_unique<TimedLifeComponent>(owner);
		break;
	case ARROW_COMPONENT:
		return std::make_unique<ArrowBehaviorComponent>(owner);
		break;
	default:
		break;
	}
	return nullptr;
}

bool ObjectFactory::Initialize(std::unique_ptr<AssetLibrary> const& aL, std::unique_ptr<PhysicsDevice> const& pD)
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
	SpriteComponent*	link_sprite = player->GetComponent<SpriteComponent>();
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;
	GAME_VEC link_pos = player->pDevice->GetPosition(player);
	GAME_FLT angle = player->pDevice->GetAngle(player);

	GOI.name = "Arrow";
	GOI.pos.x = link_pos.x;
	GOI.pos.y = link_pos.y;
	GOI.angle = -(angle - PI_2) * 180 / PI;
	GOI.movement_angle = angle;
	GOI.arrow_health = ARROW_HEALTH;
	GOI.arrow_decrement = ARROW_HEALTH_DECREMENT;
	arrow = create(componentNames, GOI);
	arrow->GetComponent<SpriteComponent>()->Initialize(link_sprite->getGDevice(), aLibrary->SearchArt("Arrow"));
	arrow->setParent(player);
	player->setChild(arrow.get());
	return arrow;
}

//Create anchor for a joint
std::unique_ptr<Object> ObjectFactory::createAnchor(Object* o, GAME_VEC pos)
{
	std::unique_ptr<Object>	anchor;
	//std::vector<std::string>	componentNames = { "Body", "Sprite"};
	std::vector<std::string>	componentNames = { "Body"};
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;

	GOI.name = "Anchor";
	GOI.pos = pos;
	GOI.angle = 0.0f;
	anchor = create(componentNames, GOI);
	//anchor->GetComponent<SpriteComponent>()->Initialize(o->GetComponent<SpriteComponent>()->getGDevice(), aLibrary->SearchArt("Rock"));
	return anchor;
}

//Create lever for a joint
std::unique_ptr<Object> ObjectFactory::createLever(GAME_VEC pos, GAME_FLT radius)
{
	std::unique_ptr<Object>	lever;
	std::vector<std::string>	componentNames = {"Body"};
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;

	GOI.name = "Lever";
	GOI.pos = pos;
	GOI.angle = 0.0f;
	GOI.shape = GAME_OTHER;
	GOI.width = 1;
	GOI.height = radius;
	lever = create(componentNames, GOI);
	return lever;
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
	loadPhysics(object, GOI);
	return object;
}

void ObjectFactory::loadPhysics(std::unique_ptr<Object> const& object, GAME_OBJECTFACTORY_INITIALIZERS const& GOI)
{
	GAME_OBJECTFACTORY_INITIALIZERS physicsGOI = *aLibrary->SearchPhysics(object->getName());

	physicsGOI.pos = GOI.pos;
	physicsGOI.angle = GOI.angle;
	if (physicsGOI.shape == GAME_CIRCLE)
	{
		physicsGOI.width = SPRITE_WIDTH;
		physicsGOI.height = 0.0f;
	}
	if (physicsGOI.shape == GAME_RECTANGLE)
	{
		physicsGOI.width = SPRITE_WIDTH;
		physicsGOI.height = SPRITE_HEIGHT;
	}
	pDevice->CreateFixture(object.get(), physicsGOI);
}