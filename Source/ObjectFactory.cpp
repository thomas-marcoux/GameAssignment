#include "ObjectFactory.h"
#include "BodyComponentFactory.h"
#include "SpriteComponentFactory.h"
#include "SlideBehaviorComponentFactory.h"
#include "CircleBehaviorComponentFactory.h.h"
#include "PlayerInputComponentFactory.h"
#include "TimedLifeComponentFactory.h"
#include "ArrowBehaviorComponentFactory.h"

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

bool ObjectFactory::Initialize(ArtAssetLibrary* aL)
{
	aLibrary = aL;
	return true;
}

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

std::unique_ptr<Object> ObjectFactory::createArrow(Object *player)
{
	std::unique_ptr<Object>	arrow;
	std::vector<std::string>	componentNames = { "Body", "Sprite", "TimedLife", "Arrow" };
	BodyComponent*	link_body = player->GetComponent<BodyComponent>();
	SpriteComponent*	link_sprite = player->GetComponent<SpriteComponent>();
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;
	GAME_VEC link_pos = link_body->getPosition();

	GOI.name = "Arrow";
	GOI.pos.x = link_pos.x;
	GOI.pos.y = link_pos.y;
	GOI.angle = link_body->getAngle();
	GOI.arrow_health = ARROW_HEALTH;
	GOI.arrow_decrement = ARROW_HEALTH_DECREMENT;
	GOI.arrow_movement = ARROW_MOVEMENT;
	arrow = create(componentNames, GOI);
	arrow->GetComponent<SpriteComponent>()->Initialize(link_sprite->getGDevice(), aLibrary->Search("Arrow"));
	return arrow;
}

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
	return object;
}
