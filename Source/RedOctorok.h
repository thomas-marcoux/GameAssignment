#ifndef REDOCTOROK_H
#define REDOCTOROK_H

#include "Object.h"

class RedOctorok : public Object
{
public:
	void Update(GAME_FLT);
	void Draw(GAME_FLT, View*);
};

#endif // !REDOCTOROK_H
