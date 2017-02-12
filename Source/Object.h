#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "Texture.h"
#include "View.h"

class Object
{
public:
	Object() {}
	~Object() {}
	void Initialize(GraphicsDevice*, InputDevice*, std::shared_ptr<Texture>, GAME_VEC, GAME_FLT);
	virtual void Update(GAME_FLT) = 0;
	virtual void Draw(GAME_FLT, View*) = 0;

protected:
	GraphicsDevice* gDevice;
	InputDevice* iDevice;
	std::shared_ptr<Texture> texture;
	GAME_VEC position;
	GAME_VEC startPosition;
	GAME_FLT angle;
};

#endif // !OBJECT_H
