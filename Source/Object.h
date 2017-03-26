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
	void Initialize(GraphicsDevice*, InputDevice*, std::shared_ptr<Texture>, GAME_VEC, GAME_FLT);
	virtual void Update(GAME_FLT) = 0;
	virtual void Draw(GAME_FLT, View*) = 0;
	GAME_VEC	getPosition() { return position; }
	GAME_FLT	getAngle() { return angle; }
	void addComponent(std::unique_ptr<Component>);

protected:
	GraphicsDevice* gDevice;
	InputDevice* iDevice;
	std::shared_ptr<Texture> texture;
	std::vector<std::unique_ptr<Component>>	components;
};

#endif // !OBJECT_H
