#ifndef TIMER_H
#define TIMER_H

#include"SDL.h"
#include"Definitions.h"

class Timer
{
public:
	Timer();
	bool Initialize(GAME_INT);
	void start();
	void stop();
	void pause();
	void unpause();
	GAME_INT getTicks();
	bool isStarted();
	bool isPaused();
	void fpsRegulate();

private:
	GAME_INT startTicks; //The clock time when the timer started
	GAME_FLT mpf; //millisecond per frame
	GAME_INT pausedTicks; //The ticks stored when the timer was paused
	bool paused;
	bool started;
};

#endif