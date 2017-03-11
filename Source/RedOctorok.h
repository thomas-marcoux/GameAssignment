#ifndef REDOCTOROK_H
#define REDOCTOROK_H

#include "Object.h"

class RedOctorok : public Object
{
public:
	RedOctorok();
	void Update(GAME_FLT);
	void Draw(GAME_FLT, View*);

private:
	GAME_FLT radius;
	GAME_FLT movementAngle;
};

#endif // !REDOCTOROK_H
