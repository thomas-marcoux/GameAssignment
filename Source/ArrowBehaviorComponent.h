#ifndef ARROWBEHAVIORCOMPONENT_H
#define ARROWBEHAVIORCOMPONENT_H

#include "Component.h"

class ArrowBehaviorComponent : public Component
{
public:
	~ArrowBehaviorComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers) { return true; }
	bool Initialize(GAME_INT);
	std::unique_ptr<Object> Update();
	bool Finish() { return false; }

private:
	GAME_FLT _movement;
};

#endif // !ARROWBEHAVIORCOMPONENT_H
