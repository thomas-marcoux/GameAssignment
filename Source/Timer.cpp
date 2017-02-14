#include "Timer.h"

Timer::Timer()
{
    startTicks = 0;
	mpf = 0.0f;
}

bool Timer::Initialize(GAME_INT fps)
{
	if (fps > 0)
	{
		mpf = (float)1000 / fps;
		return true;
	}
	return false;
	
}

void Timer::start()
{
    startTicks = SDL_GetTicks(); //Get the current clock time
}

//Gets the timer's time
GAME_INT Timer::getTicks()
{
	return SDL_GetTicks() - startTicks;
}

void Timer::fpsRegulate()
{
	//Pause for a length of time such that frame rate is maintained
	if(getTicks() < mpf)
	{
		SDL_Delay((GAME_INT)mpf - getTicks());
	}
}