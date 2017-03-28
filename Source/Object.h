#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include "Component.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "Texture.h"
#include "View.h"

//Abstract object class, enemies inherit from this class
class Object
{
public:
	Object() {}
	~Object() {}
	virtual void Update(GAME_FLT) = 0;
	virtual void Draw(GAME_FLT, View*) = 0;
	GAME_VEC	getPosition() { return position; }
	GAME_FLT	getAngle() { return angle; }
	void addComponent(std::shared_ptr<Component>);

protected:
	std::vector<std::shared_ptr<Component>>	components;
};

#endif // !OBJECT_H
