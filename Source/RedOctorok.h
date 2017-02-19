#ifndef REDOCTOROK_H
#define REDOCTOROK_H

#include "Object.h"

class RedOctorok : public Object
{
public:
	RedOctorok() { movement = REDOCTOROK_MOVEMENT; radius = REDOCTOROK_RADIUS; }
	void Update(GAME_FLT);
	void Draw(GAME_FLT, View*);

private:
	GAME_FLT radius;
};

#endif // !REDOCTOROK_H
