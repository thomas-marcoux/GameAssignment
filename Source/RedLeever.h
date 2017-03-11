#ifndef REDLEEVER_H
#define REDLEEVER_H

#include "Object.h"

class RedLeever : public Object
{
public:
	RedLeever();
	void Update(GAME_FLT);
	void Draw(GAME_FLT, View*);

private:
	GAME_INT maxDistance;
};

#endif // !REDLEEVER_H
