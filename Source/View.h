#ifndef VIEW_H
#define VIEW_H

#include "InputDevice.h"

class View
{
public:
	View() {}
	~View() {}
	bool Initialize(InputDevice*, GAME_FLT, GAME_FLT);
	bool Update(GAME_FLT);

private:
	InputDevice* iDevice;
	GAME_VEC position;
	GAME_VEC center;
};

#endif // !VIEW_H
