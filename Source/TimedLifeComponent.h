#ifndef TIMEDLIFECOMPONENT_H
#define TIMEDLIFECOMPONENT_H

#include "Component.h"

class TimedLifeComponent : public Component
{
public:
	TimedLifeComponent(std::shared_ptr<Object>);
	~TimedLifeComponent() {}
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::unique_ptr<Object> Update();
	bool Finish();

private:
	GAME_INT health;
};

#endif // !TIMEDLIFECOMPONENT_H
