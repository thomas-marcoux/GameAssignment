#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//Basic Types
typedef unsigned int	Uint32;
typedef float			GAME_FLT;
typedef Uint32			GAME_INT;
typedef struct GAME_VEC
{
    GAME_FLT x;
    GAME_FLT y;
} GAME_VEC;

//========================================
//Base Game Constants
//========================================
const GAME_INT SCREEN_WIDTH = 800;
const GAME_INT SCREEN_HEIGHT = 600;
const GAME_INT SCREEN_WIDTH_2 = SCREEN_WIDTH / 2;
const GAME_INT SCREEN_HEIGHT_2 = SCREEN_HEIGHT / 2;
const GAME_INT GAME_FPS = 100;

const GAME_INT FPS = 30;
const bool FULLSCREEN = false;
const int SPRITE_WIDTH = 16;
const int SPRITE_HEIGHT = 16;

const int WINDOW_MAX_WIDTH = SCREEN_WIDTH;
const int WINDOW_MAX_HEIGHT = SCREEN_HEIGHT;
const int WINDOW_MIN_WIDTH = WINDOW_MAX_WIDTH * (-1);
const int WINDOW_MIN_HEIGHT = WINDOW_MAX_HEIGHT * (-1);

//Event Types
enum GAME_EVENT {GAME_NA,GAME_UP,GAME_DOWN,GAME_LEFT,GAME_RIGHT, GAME_TAB, GAME_ESC, GAME_QUIT};

//Constants
const GAME_FLT PI = 3.14159f;
#define TO_RADIAN(i) i * PI / 180
#define TO_DEGREE(a) angle * 180 / PI

//Movement
const GAME_FLT BLUEOCTOROK_MOVEMENT = (float)2.0;
const GAME_FLT REDOCTOROK_MOVEMENT = (float)0.08;
const GAME_FLT REDOCTOROK_RADIUS = (float)2.0;
const GAME_FLT BLUELEEVER_MOVEMENT = (float)2.0;
const GAME_FLT REDLEEVER_MOVEMENT = (float)2.0;
const GAME_INT MAX_DISTANCE = 100;
const GAME_INT VIEW_MOVEMENT = 10;
const GAME_FLT DEFAULT_VIEW_ANGLE = 0;
const GAME_FLT VIEW_ROTATION = PI / 24;

#endif // !DEFINITIONS_H