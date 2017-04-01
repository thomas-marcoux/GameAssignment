#include <iostream>
#include "InputDevice.h"

//Initializes SDL event attribute
bool InputDevice::Initialize()
{
	_event = std::make_unique<SDL_Event>();
	if (!_event)
	{
		std::cout << "SDL Event could not initialize." << std::endl;
		return false;
	}
	_events.assign(NB_EVENTS, false);
	return true;
}

//Polls for events and returns the corresponding GAME_EVENT
void InputDevice::Update()
{
	while (SDL_PollEvent(_event.get()))
	{
		if (_event->type == SDL_QUIT)
		{
			_events[GAME_QUIT] = true;
		}
		if (_event->type == SDL_KEYDOWN)
		{
			_events[Translate()] = true;
		}
		if (_event->type == SDL_KEYUP)
		{
			_events[Translate()] = false;
		}
	}
}

//Translates the SDL_Event event to GAME_EVENT
GAME_EVENT InputDevice::Translate()
{
	switch (_event->key.keysym.sym)
	{
	case SDLK_w:
		return GAME_W;
		break;
	case SDLK_a:
		return GAME_A;
		break;
	case SDLK_s:
		return GAME_S;
		break;
	case SDLK_d:
		return GAME_D;
		break;
	case SDLK_LEFT:
		return GAME_LEFT;
		break;
	case SDLK_RIGHT:
		return GAME_RIGHT;
		break;
	case SDLK_UP:
		return GAME_UP;
		break;
	case SDLK_DOWN:
		return GAME_DOWN;
		break;
	case SDLK_SPACE:
		return GAME_SPACE;
		break;
	case SDLK_TAB:
		return GAME_TAB;
		break;
	case SDLK_ESCAPE:
		return GAME_ESC;
		break;
	}
	return GAME_NA;
}

bool InputDevice::GetEvent(GAME_EVENT event)
{
	return _events[event];
}