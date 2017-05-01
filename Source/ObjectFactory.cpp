#include "ObjectFactory.h"
#include "AssetLibrary.h"
#include "Exceptions.h"
#include "Object.h"
#include "PhysicsDevice.h"
#include "ArrowBehaviorComponent.h"
#include "CircleBehaviorComponent.h"
#include "PlayerInputComponent.h"
#include "TimedLifeComponent.h"
#include "SlideBehaviorComponent.h"
#include "SpriteComponent.h"

ObjectFactory::ObjectFactory()
{
	cLibrary["Sprite"] = SPRITE_COMPONENT;
	cLibrary["Slide"] = SLIDE_COMPONENT;
	cLibrary["Circle"] = CIRCLE_COMPONENT;
	cLibrary["Input"] = INPUT_COMPONENT;
	cLibrary["TimedLife"] = TIMEDLIFE_COMPONENT;
	cLibrary["Arrow"] = ARROW_COMPONENT;
}

//Return an instance of the requested component, nullptr if it can't be found.
std::unique_ptr<Component> ObjectFactory::Search(std::string const& component, std::unique_ptr<Object> const& owner)
{
	std::map<std::string, COMPONENT_TYPE>::iterator it = cLibrary.find(component);
	
	if (it == cLibrary.end())
		return nullptr;
	switch (it->second)
	{
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
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;

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

std::unique_ptr<Object> ObjectFactory::create(std::string const& ID, GAME_VEC const& coord)
{
	std::shared_ptr<std::vector<std::string>>	componentNames = aLibrary->SearchComponents(ID);
	std::shared_ptr<GAME_OBJECTFACTORY_INITIALIZERS>	GOI = aLibrary->SearchParameters(ID);

	if (!componentNames || !GOI)
		return nullptr;
	GOI->pos = coord;
	GOI->angle = 0.0f;
	return create(*componentNames, *GOI);
}

//Create arrow from player Object
std::unique_ptr<Object> ObjectFactory::createArrow(Object *player, GAME_FLT angle)
{
	std::unique_ptr<Object>	arrow;
	std::vector<std::string>	componentNames = {"Sprite", "TimedLife", "Arrow" };
	SpriteComponent*	link_sprite = player->GetComponent<SpriteComponent>();
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;
	GAME_VEC link_pos = player->pDevice->GetPosition(player);

	GOI.name = "Arrow"; 
	if (angle == ANGLE_UP || angle == ANGLE_DOWN)
	{
		GOI.pos.x = link_pos.x + SPRITE_WIDTH_2;
		GOI.pos.y = link_pos.y - cosf(angle) * SPRITE_HEIGHT;
	}
	if (angle == ANGLE_LEFT || angle == ANGLE_RIGHT)
	{
		GOI.pos.x = link_pos.x + sinf(angle) * SPRITE_WIDTH;
		GOI.pos.y = link_pos.y + cosf(angle) * SPRITE_HEIGHT + SPRITE_HEIGHT_2;
	}
	GOI.angle = TO_DEGREE(angle);
	GOI.arrow_health = ARROW_HEALTH;
	GOI.arrow_decrement = ARROW_HEALTH_DECREMENT;
	arrow = create(componentNames, GOI);
	arrow->GetComponent<SpriteComponent>()->Initialize(link_sprite->getGDevice(), aLibrary->SearchArt("Arrow"));
	arrow->setParent(player);
	player->setChild(arrow.get());
	return arrow;
}

//Create anchor for a joint
std::unique_ptr<Object> ObjectFactory::createAnchor(GAME_VEC pos)
{
	std::unique_ptr<Object>	anchor;
	std::vector<std::string>	componentNames;
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;

	GOI.name = "Anchor";
	GOI.pos = pos;
	GOI.angle = 0.0f;
	anchor = create(componentNames, GOI);
	return anchor;
}

//Create lever for a joint
std::unique_ptr<Object> ObjectFactory::createLever(GAME_VEC pos, GAME_FLT radius)
{
	std::unique_ptr<Object>	lever;
	std::vector<std::string>	componentNames;
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

//Create each component, call their Initialize method and add them to the new object, load physics
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

//Sets some physics attributes and create fixture
void ObjectFactory::loadPhysics(std::unique_ptr<Object> const& object, GAME_OBJECTFACTORY_INITIALIZERS const& GOI)
{
	GAME_OBJECTFACTORY_INITIALIZERS physicsGOI = *(aLibrary->SearchPhysics(object->getName()));

	physicsGOI.pos = GOI.pos;
	physicsGOI.angle = GOI.angle;
	if (physicsGOI.shape != GAME_OTHER)
	{
		physicsGOI.width = SPRITE_WIDTH_2;
		physicsGOI.height = SPRITE_HEIGHT_2;
	}
	pDevice->CreateFixture(object.get(), physicsGOI);
}