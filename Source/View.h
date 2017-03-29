#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include "Definitions.h"
#include "InputDevice.h"

class Object;

//View class, manages camera movement
class View
{
public:
	View() { objectId = 0; }
	~View() {}
	bool Initialize(InputDevice*, GAME_FLT, GAME_FLT);
	bool Update(GAME_FLT = 0.0);
	GAME_FLT getX() { return position.x; }
	GAME_FLT getY() { return position.y; }
	GAME_FLT getCenterX() { return center.x; }
	GAME_FLT getCenterY() { return center.y; }
	GAME_FLT getAngle() { return angle; }
	GAME_FLT getDegreeAngle() { return TO_DEGREE(angle); } //Returns angle in degree
	void setObjects(std::vector<std::shared_ptr<Object>>*o) { objects = o; }

private:
	void switchPerspective();

private:
	InputDevice* iDevice;
	GAME_VEC position;
	GAME_VEC center;
	GAME_FLT angle;
	std::vector<std::shared_ptr<Object>> *objects;
	GAME_INT objectId;
};

#endif // !VIEW_H
