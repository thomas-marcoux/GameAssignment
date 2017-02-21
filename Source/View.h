#ifndef VIEW_H
#define VIEW_H

#include "Definitions.h"
#include "InputDevice.h"

class View
{
public:
	View() {}
	~View() {}
	bool Initialize(InputDevice*, GAME_FLT, GAME_FLT);
	bool Update(GAME_FLT = 0.0);
	GAME_FLT getX() { return position.x; }
	GAME_FLT getY() { return position.y; }
	GAME_FLT getCenterX() { return center.x; }
	GAME_FLT getCenterY() { return center.y; }
	GAME_FLT getAngle() { return angle; }
	GAME_FLT getDegreeAngle() { return angle * 180 / PI; } //Returns angle in degree

private:
	void switchPerspective();

private:
	InputDevice* iDevice;
	GAME_VEC position;
	GAME_VEC center;
	GAME_FLT angle;
};

#endif // !VIEW_H
