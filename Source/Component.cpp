#include "Component.h"

Component::Component(std::unique_ptr<Object> const& owner)
{
	_owner = owner.get();
}
