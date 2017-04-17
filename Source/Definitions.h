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

//Physics
enum GAME_OBJECT_SHAPE { GAME_RECTANGLE, GAME_CIRCLE };
enum GAME_BODY_TYPE { GAME_STATIC, GAME_KINEMATIC, GAME_DYNAMIC };

typedef struct GAME_OBJECTFACTORY_INITIALIZERS
{
	const char*	name;
	GAME_VEC	pos;
	GAME_FLT	angle;
	GAME_FLT	movement_angle;
	bool	radius;
	bool	vertical;
	GAME_INT	arrow_health;
	GAME_INT	arrow_decrement;
	GAME_INT	arrow_movement;
	GAME_OBJECT_SHAPE	shape;
	GAME_BODY_TYPE		body_type;
	GAME_FLT	density;
	GAME_FLT	friction;
	GAME_FLT	restitution;
	GAME_FLT	angularDamping;
	GAME_FLT	linearDamping;
} GAME_OBJECTFACTORY_INITIALIZERS;

//========================================
//Base Game Constants
//========================================
#define WINDOW_NAME "Quest2"
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
	GAME_SPACE, GAME_TAB, GAME_ESC, GAME_QUIT, NB_EVENTS};

//Constants
const GAME_FLT PI = 3.14159f;
const GAME_FLT PI_2 = PI / 2;
const GAME_FLT PI2 = 2 * PI;
inline GAME_FLT TO_RADIAN(GAME_FLT d) {	return d * PI / 180; }
inline GAME_FLT TO_DEGREE(GAME_FLT r) { return r * 180 / PI; }
const float fPRV = 10.0f;

//Movement
const GAME_FLT BLUEOCTOROK_MOVEMENT_MIN = (float)0.4;
const GAME_FLT BLUEOCTOROK_MOVEMENT_MAX = (float)1.2;
const GAME_FLT REDOCTOROK_MOVEMENT = PI/356;
const GAME_FLT REDOCTOROK_RADIUS_MIN = (float)0.7;
const GAME_FLT REDOCTOROK_RADIUS_MAX = (float)1.5;
const GAME_FLT LEEVER_MOVEMENT = (float)2.0;
const int LEEVER_MIN_DISTANCE = 50;
const int LEEVER_MAX_DISTANCE = 150;
//View Movement
const GAME_INT VIEW_MOVEMENT = 5;
const GAME_FLT DEFAULT_VIEW_ANGLE = 0;
const GAME_FLT VIEW_ROTATION = PI / 36;
//Player Movement
const GAME_INT LINK_MOVEMENT = 3;
const GAME_INT DIST_TO_BORDER = 50;

//Angles
const GAME_FLT FACE_UP = PI_2;
const GAME_FLT FACE_DOWN = 3 * PI_2;
const GAME_FLT FACE_RIGHT = 0;
const GAME_FLT FACE_LEFT = PI;

//Arrow
const GAME_INT ARROW_HEALTH = 350;
const GAME_INT ARROW_HEALTH_DECREMENT = 5;
const GAME_INT ARROW_MOVEMENT = 3;

//Textures
enum TEXTURE_ID {
	TEXTURE_UP, TEXTURE_DOWN, TEXTURE_LEFT, TEXTURE_RIGHT, NB_TEXTURES
};

//Error messages
#define NO_SPRITE "Sprite not found: "
#define NO_COMPONENT "Sprite Component failed to load."
#define LOAD_ERROR "File does not exist: "
#define PARSE_ERROR "File has been corrupted: "

#endif // !DEFINITIONS_H