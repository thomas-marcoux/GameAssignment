#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <memory>

#include "Definitions.h"
#include "SDL.h"

//SDL input class
class InputDevice
{
public:
	InputDevice() {}
	~InputDevice() {}
	bool Initialize();
	GAME_EVENT GetEvent();
	GAME_EVENT Translate();

private:
	std::unique_ptr<SDL_Event> event;
};

#endif // !INPUTDEVICE_H