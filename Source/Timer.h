#ifndef TIMER_H
#define TIMER_H

#include"SDL.h"
#include"Definitions.h"

//SDL Timer class, regulates framerate
class Timer
{
public:
	Timer();
	bool Initialize(GAME_INT);
	void start();
	GAME_INT getTicks();
	void fpsRegulate();
	GAME_FLT getTime();

private:
	GAME_INT startTicks; //The clock time when the timer started
	GAME_FLT mpf; //millisecond per frame
};

#endif