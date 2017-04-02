#include "ArrowFactory.h"
#include "ArrowBehaviorComponent.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "TimedLifeComponent.h"

std::unique_ptr<Object> ArrowFactory::create(Object *owner, std::shared_ptr<Texture> texture)
{
	std::unique_ptr<Object> object = std::make_unique<Object>();
	std::unique_ptr<BodyComponent> body = std::make_unique<BodyComponent>(object);
	std::unique_ptr<SpriteComponent> sprite = std::make_unique<SpriteComponent>(object);
	std::unique_ptr<TimedLifeComponent> tlc = std::make_unique<TimedLifeComponent>(object);
	std::unique_ptr<ArrowBehaviorComponent> arrow = std::make_unique<ArrowBehaviorComponent>(object);
	BodyComponent*	link_body = owner->GetComponent<BodyComponent>();
	SpriteComponent*	link_sprite = owner->GetComponent<SpriteComponent>();

	body->setPosition(link_body->getPosition());
	body->setAngle(link_body->getAngle());
	sprite->Initialize(link_sprite->getGDevice(), texture);
	tlc->Initialize(ARROW_HEALTH, ARROW_HEALTH_DECREMENT);
	arrow->Initialize(ARROW_MOVEMENT);
	object->addComponent(std::move(body));
	object->addComponent(std::move(sprite));
	object->addComponent(std::move(tlc));
	object->addComponent(std::move(arrow));
	return std::move(object);
}
