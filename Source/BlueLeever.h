#ifndef BLUELEEVER_H
#define BLUELEEVER_H

#include "Object.h"

class BlueLeever : public Object
{
public:
	BlueLeever();
	void Update(GAME_FLT);
	void Draw(GAME_FLT, View*);

private:
	GAME_INT maxDistance;
};

#endif // !BLUELEEVER_H
