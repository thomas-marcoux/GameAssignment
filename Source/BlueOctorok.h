#ifndef BLUEOCTOROK_H
#define BLUEOCTOROK_H

#include "Object.h"

class BlueOctorok : public Object
{
public:
	void Update(GAME_FLT);
	void Draw(GAME_FLT, View*);
};

#endif // !BLUEOCTOROK_H
