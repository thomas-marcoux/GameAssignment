#ifndef REDLEEVER_H
#define REDLEEVER_H

#include "Object.h"

class RedLeever : public Object
{
public:
	RedLeever() { movement = REDLEEVER_MOVEMENT; }
	void Update(GAME_FLT);
	void Draw(GAME_FLT, View*);
};

#endif // !REDLEEVER_H
