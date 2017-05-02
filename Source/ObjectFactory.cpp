#include "ObjectFactory.h"
#include "AssetLibrary.h"
#include "Exceptions.h"
#include "Game.h"
#include "Object.h"
#include "PhysicsDevice.h"
#include "SoundDevice.h"
#include "ArrowBehaviorComponent.h"
#include "BlastBehaviorComponent.h"
#include "BombBehaviorComponent.h"
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
	cLibrary["Bomb"] = BOMB_COMPONENT;
	cLibrary["Blast"] = BLAST_COMPONENT;
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
	case BOMB_COMPONENT:
		return std::make_unique<BombBehaviorComponent>(owner);
		break;
	case BLAST_COMPONENT:
		return std::make_unique<BlastBehaviorComponent>(owner);
		break;
	default:
		break;
	}
	return nullptr;
}

bool ObjectFactory::Initialize(Game* game, std::unique_ptr<AssetLibrary> const& aL, std::unique_ptr<PhysicsDevice> const& pD,
	std::unique_ptr<SoundDevice> const& sD)
{
	aLibrary = aL.get();
	pDevice = pD.get();
	sDevice = sD.get();
	this->game = game;
	return true;
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

//Create arrow from the object
std::unique_ptr<Object> ObjectFactory::createArrow(Object *object)
{
	std::unique_ptr<Object>	arrow;
	std::vector<std::string>	componentNames = { "Sprite", "Arrow", "TimedLife" };
	GraphicsDevice*	gDevice = object->GetComponent<SpriteComponent>()->getGDevice();
	GAME_VEC	object_pos = object->pDevice->GetPosition(object);
	GAME_FLT	angle = object->pDevice->GetAngle(object);
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;

	GOI.name = "Arrow";
	GOI.pos = object_pos;
	GOI.angle = angle;
	GOI.timer = ARROW_TIMER;
	GOI.timer_speed = ARROW_TIMER_SPEED;
	arrow = create(componentNames, GOI);
	arrow->GetComponent<SpriteComponent>()->Initialize(gDevice, aLibrary->SearchArt("Arrow"));
	arrow->setParent(object);
	object->setChild(arrow.get());
	return arrow;
}

//Create bomb from player Object
std::unique_ptr<Object> ObjectFactory::createBomb(Object *player)
{
	std::unique_ptr<Object>	bomb;
	std::vector<std::string>	componentNames = {"Sprite", "Bomb", "TimedLife"};
	GraphicsDevice*	gDevice = player->GetComponent<SpriteComponent>()->getGDevice();
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;

	GOI.name = "Bomb";
	GOI.pos = player->pDevice->GetPosition(player);
	GOI.pos.x += SPRITE_WIDTH_2;
	GOI.pos.y += SPRITE_HEIGHT_2;
	GOI.angle = 0.0f;
	GOI.timer = BOMB_TIMER;
	GOI.timer_speed = BOMB_TIMER_SPEED;
	bomb = create(componentNames, GOI);
	bomb->GetComponent<BombBehaviorComponent>()->Initialize(this, sDevice);
	bomb->GetComponent<SpriteComponent>()->Initialize(gDevice, aLibrary->SearchArt("Bomb"));
	bomb->GetComponent<SpriteComponent>()->LoadTexture(TEXTURE_RED_BOMB, aLibrary->SearchArt("Red Bomb"));
	bomb->setParent(player);
	player->setChild(bomb.get());
	return bomb;
}

std::unique_ptr<Object> ObjectFactory::createBlast(Object* object)
{
	std::unique_ptr<Object>	blast;
	std::vector<std::string>	componentNames = { "Sprite", "Blast", "TimedLife" };
	GraphicsDevice*	gDevice = object->GetComponent<SpriteComponent>()->getGDevice();
	GAME_VEC	object_pos = object->pDevice->GetPosition(object);
	GAME_OBJECTFACTORY_INITIALIZERS	GOI;

	GOI.name = "Blast";
	GOI.timer = BLAST_TIMER;
	GOI.timer_speed = BLAST_TIMER_SPEED;
	for (GAME_FLT angle = 0.0f; angle < PI2; angle += PI_2)
	{
		GOI.pos = object_pos;
		if (angle == ANGLE_UP || angle == ANGLE_DOWN)
		{
			GOI.pos.x = object_pos.x + SPRITE_WIDTH_2;
			GOI.pos.y = object_pos.y - cosf(angle) * SPRITE_HEIGHT;
		}
		if (angle == ANGLE_LEFT || angle == ANGLE_RIGHT)
		{
			GOI.pos.x = object_pos.x + sinf(angle) * SPRITE_WIDTH;
			GOI.pos.y = object_pos.y + cosf(angle) * SPRITE_HEIGHT + SPRITE_HEIGHT_2;
		}
		GOI.angle = TO_DEGREE(angle);
		blast = create(componentNames, GOI);
		blast->GetComponent<SpriteComponent>()->Initialize(gDevice, aLibrary->SearchArt("Blast"));
		queueObject(std::move(blast));
	}
	return nullptr;
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

void ObjectFactory::queueObject(std::unique_ptr<Object> object)
{
	game->queueObject(std::move(object));
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
		physicsGOI.width = SPRITE_WIDTH_2 * 0.8f;
		physicsGOI.height = SPRITE_HEIGHT_2 * 0.8f;
	}
	pDevice->CreateFixture(object.get(), physicsGOI);
}