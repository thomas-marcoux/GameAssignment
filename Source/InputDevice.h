#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <memory>

#include <vector>
#include "Definitions.h"
#include "SDL.h"

//SDL input class
class InputDevice
{
public:
	InputDevice() {}
	~InputDevice() {}
	bool Initialize();
	void Update();
	bool GetEvent(GAME_EVENT);

private:
	GAME_EVENT Translate();

private:
	std::unique_ptr<SDL_Event> _event;
	std::vector<bool>	_events;
};

#endif // !INPUTDEVICE_H