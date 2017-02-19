#ifndef BLUELEEVER_H
#define BLUELEEVER_H

#include "Object.h"

class BlueLeever : public Object
{
public:
	BlueLeever() { movement = BLUELEEVER_MOVEMENT; }
	void Update(GAME_FLT);
	void Draw(GAME_FLT, View*);
};

#endif // !BLUELEEVER_H
