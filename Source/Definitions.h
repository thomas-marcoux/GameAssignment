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
typedef struct GAME_OBJECTFACTORY_INITIALIZERS
{
	const char*	name;
	GAME_VEC	pos;
	GAME_FLT	angle;
	bool	radius;
	bool	vertical;
} GAME_OBJECTFACTORY_INITIALIZERS;

//========================================
//Base Game Constants
//========================================
#define WINDOW_NAME "Quest1"
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
enum GAME_EVENT {GAME_NA, GAME_W, GAME_A, GAME_S, GAME_D,
	GAME_UP,GAME_DOWN,GAME_LEFT,GAME_RIGHT,
	GAME_TAB, GAME_ESC, GAME_QUIT, NB_EVENTS};

//Constants
const GAME_FLT PI = 3.14159f;
const GAME_FLT PI2 = 2 * PI;
#define TO_RADIAN(i) i * PI / 180
#define TO_DEGREE(a) a * 180 / PI

//Movement
const GAME_FLT BLUEOCTOROK_MOVEMENT_MIN = (float)0.4;
const GAME_FLT BLUEOCTOROK_MOVEMENT_MAX = (float)1.2;
const GAME_FLT REDOCTOROK_MOVEMENT = PI/356;
const GAME_FLT REDOCTOROK_RADIUS_MIN = (float)0.7;
const GAME_FLT REDOCTOROK_RADIUS_MAX = (float)1.5;
const GAME_FLT LEEVER_MOVEMENT = (float)2.0;
const int LEEVER_MIN_DISTANCE = 50;
const int LEEVER_MAX_DISTANCE = 150;
const GAME_INT LINK_MOVEMENT = 3;
const GAME_FLT LINK_ROTATION = PI / 6;
const GAME_INT VIEW_MOVEMENT = 5;
const GAME_FLT DEFAULT_VIEW_ANGLE = 0;
const GAME_FLT VIEW_ROTATION = PI / 36;

#endif // !DEFINITIONS_H