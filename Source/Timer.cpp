#include "Timer.h"

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
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
    started = true;
    paused = false;
    startTicks = SDL_GetTicks(); //Get the current clock time
}

void Timer::stop()
{
    started = false;
    paused = false;
}

//If the timer is running and isn't already paused, pause it
void Timer::pause()
{
    if((started == true) && (paused == false))
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

//Reset the starting ticks and paused ticks
void Timer::unpause()
{
    if( paused == true )
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

//Gets the timer's time
GAME_INT Timer::getTicks()
{
    if( started == true )
    {
        if( paused == true )
            return pausedTicks;
        else
            return SDL_GetTicks() - startTicks;
    }
    return 0;
}

bool Timer::isStarted()
{
    return started;
}

bool Timer::isPaused()
{
    return paused;
}

//Pause for a length of time such that frame rate is maintained
void Timer::fpsRegulate()
{
	if(getTicks() < mpf)
	{
		SDL_Delay((GAME_INT)mpf - getTicks());
	}
}