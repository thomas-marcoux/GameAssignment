#ifndef BOMBBEHAVIORCOMPONENT_H
#define BOMBBEHAVIORCOMPONENT_H

#include "Component.h"

class BombBehaviorComponent : public Component
{
public:
	BombBehaviorComponent(std::unique_ptr<Object> const& owner) : Component(owner) {}
	~BombBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS const& initializers);
	std::unique_ptr<Object> Update(GAME_FLT);
	bool Finish() { return false; }
	void blast();

private:
	;
};

#endif // !BOMBBEHAVIORCOMPONENT_H
