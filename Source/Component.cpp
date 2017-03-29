#include "Component.h"

Component::Component(std::shared_ptr<Object> owner)
{
	_owner = owner;
}
