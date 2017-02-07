#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include "InputDevice.h"
#include "Texture.h"
#include "View.h"

class Object
{
public:
	Object() {}
	~Object() {}
	virtual void Update(GAME_FLT) = 0;
	virtual void Draw(GAME_FLT, View*) = 0;

private:
	GraphicsDevice* gDevice;
	InputDevice* iDevice;
	std::shared_ptr<Texture> texture;
	GAME_VEC position;
	GAME_VEC startPosition;
	GAME_FLT angle;
};

#endif // !OBJECT_H
