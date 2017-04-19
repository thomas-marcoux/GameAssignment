#include "Timer.h"

Timer::Timer()
{
    startTicks = 0;
	mpf = 0.0f;
}

//Sets mpf in accordance with fps
bool Timer::Initialize(GAME_INT fps)
{
	if (fps > 0)
	{
		mpf = (float)1000 / fps;
		return true;
	}
	return false;
	
}

//Get the current clock time
void Timer::start()
{
    startTicks = SDL_GetTicks();
}

//Gets the timer's time
GAME_INT Timer::getTicks()
{
	return SDL_GetTicks() - startTicks;
}

//Pause for a length of time such that frame rate is maintained
void Timer::fpsRegulate()
{
	if(getTicks() < mpf)
	{
		SDL_Delay((GAME_INT)mpf - getTicks());
	}
}

//Gets physics time
GAME_FLT Timer::getTime()
{
	return SDL_GetTicks() / 50.0f;
}