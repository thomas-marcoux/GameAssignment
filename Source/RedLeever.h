#ifndef REDLEEVER_H
#define REDLEEVER_H

#include "Object.h"

class RedLeever : public Object
{
public:
	void Update(GAME_FLT);
	void Draw(GAME_FLT, View*);
};

#endif // !REDLEEVER_H
