#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <memory>

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

InputDevice::InputDevice()
{
}

InputDevice::~InputDevice()
{
}

#endif // !INPUTDEVICE_H