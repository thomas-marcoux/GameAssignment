#include "Object.h"

//Initializes object
void Object::Initialize(GraphicsDevice *g, InputDevice *i, std::shared_ptr<Texture> t, GAME_VEC s, GAME_FLT a)
{
	gDevice = g;
	iDevice = i;
	texture = t;
	startPosition = s;
	position = s;
	angle = a;
}
